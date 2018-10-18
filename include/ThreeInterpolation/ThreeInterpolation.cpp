//
// Created by fw on 18/10/17.
// E-mail: zjufanwu@zju.edu.cn
//
#include "ThreeInterpolation.h"

namespace dmotion {
    ThreeInterpolation::ThreeInterpolation(const std::vector<double> &x_array,
                                           const std::vector<double> &y_array,
                                           const std::vector<double> &s_angle) {
        piece_num_ = x_array.size();
        poly_ptr_ = new Polynomial<3>[piece_num_];
    }

    ThreeInterpolation::ThreeInterpolation(const dmotion::ThreeInterpolation &intpo) {

    }

}

