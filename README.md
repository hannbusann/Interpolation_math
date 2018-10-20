# Interpolation_math

A new interpolation algorithm, which can customize the displacement and velocity of each sample point.

## Prerequisites

These tools depend on Eigen modules (mainly Dense) and C++ Standard Library. You'd better install Eigen3 in advance.

#### For linux

`sudo apt-get install libeigen3-dev`

#### For Mac

`brew install eigen`

The namespace can be changed if necessary.

---

## Tree

```.
├── CMakeLists.txt
├── include
│   ├── Polynomial
│   │   ├── Polynomial.hpp
│   │   └── PolynomialInternal.hpp
│   ├── ThreeInterpolation
│   │   ├── ThreeInterpolation.cpp
│   │   └── ThreeInterpolation.h
│   ├── ThreeSpline
│   │   └── SimpleInterpolation.hpp
│   └── Utility
│       └── dmotion_math.hpp
├── matlab
│   └── three_try.m
├── README.md
└── test
    └── three_try.cpp
```

---

## Functions

In ThreeInterpolation folder, the source file **ThreeInterpolation.cpp** and header file **ThreeInterpolation.h** declare and define the **ThreeInterpolation** class. Specific annotations are in code, temporarily only Chinese explaination contained.

#### ThreeInterpolation /~ThreeInterpolation

 There are two overrided conductor functions in this class. Copy conductor and destructor are default.

#### EvalHere

Get the value of the derived piecewise three degress polynomial function at one particular point <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{150}&space;x_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;x_0" title="x_0" /></a>

#### CalculatePoints

Calculate the value of the derived piecewise three degress polynomial function at an arithmetic progression with common difference of <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\fn_jvn&space;\large&space;t_{0}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\fn_jvn&space;\large&space;t_{0}" title="\large t_{0}" /></a>.

#### GetPoints

Return the the value of the derived piecewise three degress polynomial function at an arithmetic progression with common difference of <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\fn_jvn&space;\large&space;t_{0}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\fn_jvn&space;\large&space;t_{0}" title="\large t_{0}" /></a> after CalculatePoints.

#### GetTimes

Return the arithmetic progression with common difference of <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\fn_jvn&space;\large&space;t_{0}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\fn_jvn&space;\large&space;t_{0}" title="\large t_{0}" /></a>.

#### AddPoint

Add a sample point with its horizontal coordinates <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\fn_jvn&space;\large&space;x_a" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\fn_jvn&space;\large&space;x_a" title="\large x_a" /></a>, vertical coordinates <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\fn_jvn&space;\large&space;y_a" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\fn_jvn&space;\large&space;y_a" title="\large y_a" /></a> and slope <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\fn_jvn&space;\large&space;s_a" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\fn_jvn&space;\large&space;s_a" title="\large s_a" /></a> into this ThreeInterpolation object.

#### GetCoef

Get <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\fn_jvn&space;\large&space;piece_{num}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\fn_jvn&space;\large&space;piece_{num}" title="\large piece_{num}" /></a>th section of three degress polynomial's coefficients.

