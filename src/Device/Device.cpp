#include "Device.h"

Device::Device() {
}

Device::~Device() {
}

//void Device::setConstValue(double value) {
//}

void Device::getSubA(Eigen::MatrixXd& subA) {
}

void Device::getSubB(Eigen::MatrixXd& SubB) {
}

void Device::getSubEIntegral(Eigen::VectorXd& subE, double* tList) {
}

void Device::getSubPandPJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian) {
}

void Device::getSubQandQJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian) {
}

void Device::getSubC(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subC) {
}

int Device::getReturnPrime()
{
	return 0;
}

void Device::setDeviceInfo(map<string, int>& _PortMap)
{
}

void Device::setInputData(InputStr _DataStr, map<string, int>& _PortData)
{
}

DeviceInfoStr Device::getDeviceInfo()
{
	DeviceInfoStr str_null;
	return str_null;
}

string Device::getInstanceName()
{
	return InstanceName;
}