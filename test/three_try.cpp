#include <iostream>
#include "../include/ThreeInterpolation/ThreeInterpolation.h"
#include "../include/Utility/dmotion_math.hpp"

using namespace std;
using namespace dmotion;

int main(int argc, char **argv) {
    vector<double> xx = {-4,3,8};
    vector<double> yy = {3, 5,4};
    vector<double> ss = {2, 1,-3};
    ThreeInterpolation object(xx, yy, ss);
    cout << object.GetCoef(1) << endl;
    object.CalculatePoinsts();

    dmotion::PrintVector(object.GetPoints());
    //dmotion::PrintVector(object.GetTimes());


    return 0;

}