#include <iostream>
#include "../include/ThreeInterpolation/ThreeInterpolation.h"
#include "../include/Utility/dmotion_math.hpp"

using namespace std;
using namespace dmotion;

int main(int argc, char **argv) {
    vector<double> xx = {-4,3,3,8};
    vector<double> yy = {3, 5,6,4};
    vector<double> ss = {2, 1,-3};
    ThreeInterpolation object(xx, yy, ss);
    cout << object.GetCoef(1) << endl;
    object.CalculatePoints(110);
    dmotion::PrintVector(object.GetPoints());
    cout<<endl;
    dmotion::PrintVector(object.GetTimes());
    cout<< endl<<endl;

    object.AddPoint(1,6,-1);
    object.CalculatePoints(100);
    dmotion::PrintVector(object.GetPoints());
    cout<<endl;
    dmotion::PrintVector(object.GetTimes());
    //dmotion::PrintVector(object.GetTimes());


    ThreeInterpolation obb(xx, yy);
    cout << "no slopes" << endl;
    dmotion::PrintVector(obb.GetPoints());
    dmotion::PrintVector(obb.GetTimes());
    return 0;

}