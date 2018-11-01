//
// Created by fw on 18/10/17.
// E-mail: zjufanwu@zju.edu.cn
//
#include "ThreeInterpolation.h"
#include <cmath>
#include <vector>
#include <iostream>

namespace dmotion {
    /**
     * 标准的构造函数
     * @param x_array  样本点的x坐标序列，dmoiton工程中是时间，单位为s，通常从0开始
     * @param y_array  样本点的y坐标序列，dmotion工程中是肢端坐标值
     * @param s_angle  样本点的倾斜角度，dmotion工程中是肢端坐标值的变化速度
     */
    ThreeInterpolation::ThreeInterpolation(const std::vector<double> &x_array,
                                           const std::vector<double> &y_array,
                                           const std::vector<double> &s_angle) {
        x_array_ = x_array;
        y_array_ = y_array;
        s_angle_ = s_angle;

        if (isInOrder(x_array_)) {
            piece_num_ = static_cast<int>(x_array_.size() - 1);
            Calculate();
        } else
            std::cerr << "The x_array is not available!" << std::endl;
    }


    /**
     * 没有斜率输入的构造函数，默认斜率都是0
     * @param x_array
     * @param y_array
     */
    ThreeInterpolation::ThreeInterpolation(const std::vector<double> &x_array,
                                           const std::vector<double> &y_array) {
        x_array_ = x_array;
        y_array_ = y_array;
        std::vector<double> s_tmp(x_array_.size(), 0);
        s_angle_ = s_tmp;
        if (isInOrder(x_array_)) {
            piece_num_ = static_cast<int>(x_array_.size() - 1);
            Calculate();
        } else
            std::cerr << "The x_array is not available!" << std::endl;
    }

    /**
     * 默认的析构函数，留在这里以防备用
     */
    ThreeInterpolation::~ThreeInterpolation() = default;
    /**
     * 判定输入的x_array序列是否合格
     * @param x_ar 输入的x_array序列
     * @return 返回是否合格的bool值
     */
    bool ThreeInterpolation::isInOrder(std::vector<double> &x_ar) {
        unsigned i = 0;
        do {
            if (x_ar[i] > x_ar[i + 1])
                return false;
            else if (x_ar[i] == x_ar[i + 1]) {
                x_ar.erase(x_ar.begin() + i);
                y_array_.erase(y_array_.begin() + i);
                s_angle_.erase(s_angle_.begin() + i);
            } else
                i++;
        } while (i < (x_ar.size() - 1));
        return true;
    }

    /**
     * 用于计算的一步，完成分段多项式的计算
     */
    void ThreeInterpolation::Calculate() {
        poly_.clear();
        for (int i = 0; i < piece_num_; i++) {
            Eigen::Vector4d B(y_array_[i], s_angle_[i], y_array_[i + 1], s_angle_[i + 1]);
            Eigen::Matrix4d A;
            A << pow(x_array_[i], 3), pow(x_array_[i], 2), x_array_[i], 1,
                    3 * pow(x_array_[i], 2), 2 * x_array_[i], 1, 0,
                    pow(x_array_[i + 1], 3), pow(x_array_[i + 1], 2), x_array_[i + 1], 1,
                    3 * pow(x_array_[i + 1], 2), 2 * x_array_[i + 1], 1, 0;

            Eigen::Matrix<double, 4, 1> coef_solved = A.lu().solve(B);
            poly_.emplace_back(coef_solved);
        }
    }
    /**
     * 获得分段三次插值曲线某一点的值
     * @param x0 欲获得坐标点的横坐标
     * @return 返回这个x0对应的坐标值
     */
    double ThreeInterpolation::EvalHere(double x0) const {
        int i;
        for (i = 0; i < piece_num_; i++) {
            if (x0 >= x_array_[i] && x0 <= x_array_[i + 1])
                break;
        }
        if (i == piece_num_) {
            std::cerr << "x is beyond the domain of definition! " << "error:"
                      << x0 << " is not between " << x_array_[0]
                      << " and " << x_array_[piece_num_] << "." << std::endl;
            return 0;
        }
        return poly_[i].eval(x0);

    }
    /**
     * 用于获得固定时间间隔的分段三次曲线的值，无返回值
     * @param t0_in 时间序列的间隔，单位为ns
     */
    void ThreeInterpolation::CalculatePoints(int t0_in) {
        x_samples_.clear();
        y_samples_.clear();
        double t_tmp = x_array_[0];
        double t0;
        t0 = static_cast<double> (t0_in) / 1000;
        do {
            y_samples_.emplace_back(EvalHere(t_tmp));
            x_samples_.emplace_back(t_tmp);
            t_tmp += t0;
        } while (t_tmp < x_array_[piece_num_]);
        y_samples_.emplace_back(EvalHere(x_array_[piece_num_]));
        x_samples_.emplace_back(x_array_[piece_num_]);
    }

    /**
     * 在Calculate后获得某一分段的三次多项式的四个系数
     * @param piece_num_in 想要获得第几个分段的多项式系数
     * @return
     */
    Eigen::Matrix<double, 4, 1> ThreeInterpolation::GetCoef(int piece_num_in) const {
        if (piece_num_in < 1 || piece_num_in > piece_num_) {
            Eigen::Matrix<double, 4, 1> n;
            std::cerr << "The number of this piece is beyond range. " << std::endl;
            n << 0, 0, 0, 0;
            return n;
        }
        return poly_[piece_num_in - 1].coefficients();
    }

    /**
     * 在CalculatePoints之后获得计算出来的点的坐标值
     * @return 返回这些坐标点的vector
     */
    std::vector<double> &ThreeInterpolation::GetPoints() {
        return y_samples_;
    }

    /**
     * 在CalculatePoints之后获得计算出来的时间点，作为舵机发值的时间戳
     * @return 返回这些时间点的vector
     */
    std::vector<double> &ThreeInterpolation::GetTimes() {
        return x_samples_;
    }

    /**
     * 用来加一个样本点的函数
     * @param x_a 新加样本点的横坐标值
     * @param y_a 新加样本点的纵坐标值
     * @param s_a 新加样本点的斜率值
     */
    void ThreeInterpolation::AddPoint(double x_a, double y_a, double s_a) {
        int i;

        /**
         *  //  先判定x_a在哪个区间
         *  //  举例：原本有4个点，根据x_a落入如下区间的位置定i的值
         *  //  piece_num_ = 3
         *  //  x_array_.size() = 4
         *  //  (   i=0   )[•   i=1   )[•   i=2   )[•   i=3   )[•   i=4   )
         */
        for (i = 0; i < piece_num_; i++) {
            if (x_a < x_array_[0]) {
                i = 0;
                break;
            }
            if (x_a > x_array_[piece_num_]) {
                i = piece_num_ + 1;
                break;
            }
            if (x_a >= x_array_[i] && x_a < x_array_[i + 1]) {
                i++;
                break;
            }
        }
        /**
         *  //  在确定了x_a在哪个空间后，分情况对这几种情况对已有的poly_ 进行改造
         */
        if (i == 0) {
            //std::cout << std::endl << "this is good:" << i << std::endl;
            Eigen::Vector4d B(y_a, s_a, y_array_[0], s_angle_[0]);
            Eigen::Matrix4d A;
            A << pow(x_a, 3), pow(x_a, 2), x_a, 1,
                    3 * pow(x_a, 2), 2 * x_a, 1, 0,
                    pow(x_array_[0], 3), pow(x_array_[0], 2), x_array_[0], 1,
                    3 * pow(x_array_[0], 2), 2 * x_array_[0], 1, 0;
            Eigen::Matrix<double, 4, 1> coef_solved = A.lu().solve(B);

            poly_.insert(poly_.begin(), Polynomial<3>(coef_solved));
            x_samples_.clear();
            y_samples_.clear();
            x_array_.insert(x_array_.begin(), x_a);
            y_array_.insert(y_array_.begin(), y_a);
            s_angle_.insert(s_angle_.begin(), s_a);
            piece_num_++;
        } else if (i == piece_num_ + 1) {
            //std::cout << std::endl << "this is good:" << i << std::endl;
            Eigen::Vector4d B(y_a, s_a, y_array_[piece_num_], s_angle_[piece_num_]);
            Eigen::Matrix4d A;
            A << pow(x_a, 3), pow(x_a, 2), x_a, 1,
                    3 * pow(x_a, 2), 2 * x_a, 1, 0,
                    pow(x_array_[piece_num_], 3), pow(x_array_[piece_num_], 2), x_array_[piece_num_], 1,
                    3 * pow(x_array_[piece_num_], 2), 2 * x_array_[piece_num_], 1, 0;
            Eigen::Matrix<double, 4, 1> coef_solved = A.lu().solve(B);

            poly_.emplace_back(coef_solved);
            x_samples_.clear();
            y_samples_.clear();
            x_array_.emplace_back(x_a);
            y_array_.emplace_back(y_a);
            s_angle_.emplace_back(s_a);
            piece_num_++;
        } else {
            //std::cout << std::endl << "this is good:" << i << std::endl;
            Eigen::Vector4d B_up(y_a, s_a, y_array_[i - 1], s_angle_[i - 1]);
            Eigen::Matrix4d A_up;
            A_up << pow(x_a, 3), pow(x_a, 2), x_a, 1,
                    3 * pow(x_a, 2), 2 * x_a, 1, 0,
                    pow(x_array_[i - 1], 3), pow(x_array_[i - 1], 2), x_array_[i - 1], 1,
                    3 * pow(x_array_[i - 1], 2), 2 * x_array_[i - 1], 1, 0;
            Eigen::Matrix<double, 4, 1> coef_solved_up = A_up.lu().solve(B_up);

            Eigen::Vector4d B_down(y_a, s_a, y_array_[i], s_angle_[i]);
            Eigen::Matrix4d A_down;
            A_down << pow(x_a, 3), pow(x_a, 2), x_a, 1,
                    3 * pow(x_a, 2), 2 * x_a, 1, 0,
                    pow(x_array_[i], 3), pow(x_array_[i], 2), x_array_[i], 1,
                    3 * pow(x_array_[i], 2), 2 * x_array_[i], 1, 0;
            Eigen::Matrix<double, 4, 1> coef_solved_down = A_down.lu().solve(B_down);

            poly_.erase(poly_.begin() + i - 1);
            poly_.insert(poly_.begin() + i - 1, Polynomial<3>(coef_solved_up));
            poly_.insert(poly_.begin() + i, Polynomial<3>(coef_solved_down));
            x_samples_.clear();
            y_samples_.clear();
            x_array_.insert(x_array_.begin() + i, x_a);
            y_array_.insert(y_array_.begin() + i, y_a);
            s_angle_.insert(s_angle_.begin() + i, s_a);
            piece_num_++;
        }
    }


}






