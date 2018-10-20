cmake_minimum_required(VERSION 2.8.3)
project(threespline_try)
add_definitions(-std=c++11 -Wall -O2)

find_package( Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories(./include/Polynomial
        ./include/ThreeInterpolation
        ./include/Utility)
add_library(ThreeInterpolate ./include/ThreeInterpolation/ThreeInterpolation.cpp)

add_executable(three_try test/three_try.cpp )
target_link_libraries(three_try ThreeInterpolate )
# include/Utility/EigenTypes.h )
