//
// Created by fw on 18/10/17.
// E-mail: zjufanwu@zju.edu.cn
//

#ifndef DMOTION_MATH_HPP
#define DMOTION_MATH_HPP

#include <vector>
#include <cmath>

namespace dmotion {


    /*
     * 把曲线斜率化为倾斜角（角度制）的函数
     */
    template<class T>
    double Slope_to_AngleDeg(T s) {
        return atan(s) * 57.3;
    }
    /*
     * 角度制到弧度值的转换
     */
    template<class T>
    inline T Deg2Rad(T deg) {
        return deg * M_PI / 180;
    }
    /*
     * 弧度值到角度值的转换
     */
    template<class T>
    inline T Rad2Deg(T rad) {
        return rad * 180 / M_PI;
    }


}


#endif //DMOTION_MATH_HPP
