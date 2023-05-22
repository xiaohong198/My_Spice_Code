#pragma once
#include "Device.h"

class Resistor :public Device
{
private:
	double resistance;
private:
	DeviceInfoStr DeviceInfo_;
public:
	Resistor();
	~Resistor();

	void setConstValue(double);

	//void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
	void getSubA(Eigen::MatrixXd& subA);
	int getReturnPrime();
	void setDeviceInfo_(vector<int>);
	DeviceInfoStr getDeviceInfo_();
};

