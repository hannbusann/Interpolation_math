//
// Created by fw on 18/10/17.
// E-mail: zjufanwu@zju.edu.cn
//

#ifndef THREEINTERPOLATION_H
#define THREEINTERPOLATION_H

#include <vector>
#include <Eigen/Dense>
#include <Eigen/LU>
#include "../Polynomial/Polynomial.hpp"


namespace dmotion {

    class ThreeInterpolation {
    private:
        int piece_num_;
        std::vector<dmotion::Polynomial<3>> poly_;
        std::vector<double> x_array_;       //样本点的x坐标序列，dmoiton工程中是时间
        std::vector<double> y_array_;       //样本点的y坐标序列，dmotion工程中是肢端坐标值
        std::vector<double> s_angle_;       //样本点的倾斜角度，dmotion工程中是肢端坐标值的变化速度

    public:
        //参数健全的构造函数
        ThreeInterpolation(const std::vector<double> &x_array,
                           const std::vector<double> &y_array,
                           const std::vector<double> &s_angle);


        //拷贝构造函数
        ThreeInterpolation(const ThreeInterpolation &interpo_in);

        //析构函数
        ~ThreeInterpolation();

        //经过这一步计算，算出这些分段多项式的Polynomial对象
        void Calculate();

        //获得曲线所对应的函数的定义域中的某一x点的函数值
        double EvalHere(double x0);

        //获得固定时间间隔下样本点的Eval序列，时间t0是这个间隔时间，单位是ms,有默认毫秒数20ms
        std::vector<double> &GetPoints(int t0 = 20);

        //添加一个点，并重新进行calculate这一步
        void AddPoint(double x_a, double y_a);

        //查看一个分段的三次多项式系数
        Eigen::Matrix<double, 4, 1> GetCoef(int piece_num);

    };

}


#endif // THREEINTERPOLATION_H
