#pragma once
#include "Device.h"

class Vsource_DC:public Device
{
private:
	double V_DC;
private:
	DeviceInfoStr DeviceInfo_;

public:
	Vsource_DC();
	~Vsource_DC();
	void setConstValue(double);

	double eFunction(double);
	//void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double);
	double setIntegration(double*);
	//void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double);
	void getSubA(Eigen::MatrixXd& subA);
	void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);
	int getReturnPrime();
	void setDeviceInfo_(vector<int>);
	DeviceInfoStr getDeviceInfo_();
};

