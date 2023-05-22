#include "Vsource_DC.h"

Vsource_DC::Vsource_DC() {
    V_DC = 20;
}

void Vsource_DC::setConstValue(double vdc) {
    V_DC = vdc;
}

double Vsource_DC::eFunction(double t) {
    return V_DC;
}

//void Vsource_DC::getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double t) {
//    subA.setZero();
//    subA(0, 2) = 1;
//    subA(1, 2) = -1;
//    subA(2, 0) = 1;
//    subA(2, 1) = -1;
//    subE.setZero();
//    subE(2) = eFunction(t);
//}

double Vsource_DC::setIntegration(double* tList) {
    return V_DC * (tList[1] - tList[0]);
}

//void Vsource_DC::getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double t1, double t2) {
//    subA.setZero();
//    subA(0, 2) = 1;
//    subA(1, 2) = -1;
//    subA(2, 0) = 1;
//    subA(2, 1) = -1;
//    subEIntegral.setZero();
//    subEIntegral(2) = setIntegration(t1,t2);
//}

Vsource_DC::~Vsource_DC() {
}

void Vsource_DC::getSubA(Eigen::MatrixXd& subA) {
    subA.setZero();
    subA(0, 2) = 1;
    subA(1, 2) = -1;
    subA(2, 0) = 1;
    subA(2, 1) = -1;
}

void Vsource_DC::getSubEIntegral(Eigen::VectorXd& subEIntegral, double* tList) {
    subEIntegral.setZero();
    subEIntegral(2) = setIntegration(tList);
}

int Vsource_DC::getReturnPrime()
{
	return PrimeA + PrimeE;
}

void Vsource_DC::setDeviceInfo_(vector<int> _index)
{
	DeviceInfo_.xIndex = _index;
}

DeviceInfoStr Vsource_DC::getDeviceInfo_()
{
	return DeviceInfo_;
}