#include <iostream>
#include "Resistor.h"

using namespace std;

Resistor::Resistor() {
    resistance = 1;
}

void Resistor::setConstValue(double value) {
    resistance = value;
}

//void Resistor::getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB) {
//    subA(0,0) = 1/resistance;
//    subA(0,1) = -1/resistance;
//    subA(1,0) = -1/resistance;
//    subA(1,1) = 1/resistance;
//    subB.setZero();
//}

void Resistor::getSubA(Eigen::MatrixXd& subA) {
    subA(0, 0) = 1 / resistance;
    subA(0, 1) = -1 / resistance;
    subA(1, 0) = -1 / resistance;
    subA(1, 1) = 1 / resistance;
}

int Resistor::getReturnPrime()
{
	return PrimeA;
}

void Resistor::setDeviceInfo_(vector<int> _index)
{
	DeviceInfo_.xIndex = _index;
}

DeviceInfoStr Resistor::getDeviceInfo_()
{
	return DeviceInfo_;
}
Resistor::~Resistor() {

}