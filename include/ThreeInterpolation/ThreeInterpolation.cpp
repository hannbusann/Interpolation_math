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
     * 用于计算的一步，完成分段多项式的计算和时间点的
     * @param t0_in
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

    void ThreeInterpolation::CalculatePoinsts(int t0_in) {
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

    Eigen::Matrix<double, 4, 1> ThreeInterpolation::GetCoef(int piece_num_in) const {
        if (piece_num_in < 1 || piece_num_in > piece_num_) {
            Eigen::Matrix<double, 4, 1> n;
            n << 0, 0, 0, 0;
            return n;
        }
        return poly_[piece_num_in - 1].coefficients();
    }

    std::vector<double> &ThreeInterpolation::GetPoints() {

        return y_samples_;
    }

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

        /*
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
            if (x_a >= x_array_[i] && x_a < x_array_[i + 1])
                break;
        }



    }


}

