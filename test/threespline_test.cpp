// #include "inlcude/ThreeSpline/SimpleInterpolation.hpp"
#include <iostream>
#include <EigenTypes.h>
using namespace std;

int main (int argc, char **argv)
{
	Matrix2X<float> m_2(2,3);
	m_2 << 1,12,2,2,2,2;
	cout << m_2 <<endl;
}