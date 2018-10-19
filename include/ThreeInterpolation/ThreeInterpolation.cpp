//
// Created by fw on 18/10/17.
// E-mail: zjufanwu@zju.edu.cn
//
#include "ThreeInterpolation.h"
#include <cmath>
#include <vector>
#include <iostream>

namespace dmotion {
    ThreeInterpolation::ThreeInterpolation(const std::vector<double> &x_array,
                                           const std::vector<double> &y_array,
                                           const std::vector<double> &s_angle)
            : x_array_(x_array), y_array_(y_array),
              s_angle_(s_angle) {
        piece_num_ = x_array.size() - 1;
    }

    ThreeInterpolation::ThreeInterpolation(const dmotion::ThreeInterpolation &interpo_in) {}

    ThreeInterpolation::~ThreeInterpolation() = default;

    void ThreeInterpolation::Calculate() {
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

    Eigen::Matrix<double, 4, 1> ThreeInterpolation::GetCoef(int piece_num_in) {
        if (piece_num_in < 1 || piece_num_in > piece_num_) {
            Eigen::Matrix<double, 4, 1> n;
            n << 0, 0, 0, 0;
            return n;
        }
        return poly_[piece_num_in - 1].coefficients();
    }

}

