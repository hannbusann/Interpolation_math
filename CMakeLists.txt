cmake_minimum_required(VERSION 2.8.3)
project(threespline_try)
add_definitions(-std=c++11 -Wall -O2)

find_package( Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories( ./include/Utility)


add_executable(threespline_try test/threespline_test.cpp include/ThreeSpline/ThreeSpline.h)

# include/Utility/EigenTypes.h )