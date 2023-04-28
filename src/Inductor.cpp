#include "Inductor.h"
Inductor::Inductor() {
    Inductance = 1;
}

Inductor::~Inductor() {
}

void Inductor::setConstValue(double L) {
    Inductance = L;
}

//void Inductor::getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB) {
//    subA.setZero();
//    subA(0, 2) = 1;
//    subA(1, 2) = -1;
//    subA(2, 0) = -1;
//    subA(2, 1) = 1;
//    subB.setZero();
//    subB(2, 2) = Inductance;
//}

void Inductor::getSubA(Eigen::MatrixXd& subA) {
    subA(0, 2) = 1;
    subA(1, 2) = -1;
    subA(2, 0) = -1;
    subA(2, 1) = 1;
}

void Inductor::getSubB(Eigen::MatrixXd& subB) {
    subB.setZero();
    subB(2, 2) = Inductance;
}

int Inductor::getReturnPrime()
{
	return PrimeA * PrimeB;
}

void Inductor::setDeviceInfo_(vector<int> _index)
{
	DeviceInfo_.xIndex = _index;
}

DeviceInfoStr Inductor::getDeviceInfo_()
{
	return DeviceInfo_;
}