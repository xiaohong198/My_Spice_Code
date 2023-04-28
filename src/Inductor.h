#pragma once
#include "Solver.h"
#include "Device.h"
class Solver;
class Inductor :public Device
{
private:
	double Inductance;
private:
	DeviceInfoStr DeviceInfo_;

public:
	Inductor();
	~Inductor();

	void setConstValue(double);
//	void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
	void getSubA(Eigen::MatrixXd& subA);
	void getSubB(Eigen::MatrixXd& subB);
	int getReturnPrime();
	void setDeviceInfo_(vector<int>);
	DeviceInfoStr getDeviceInfo_();
};



