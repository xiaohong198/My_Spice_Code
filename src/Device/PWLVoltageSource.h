#pragma once
#include "Device.h"
class PWLVoltageSource:public Device
{
protected:
	int tCount;
	double* tList;
	double* vList;//默认按照从小到大输入
private:
	DeviceInfoStr DeviceInfo_;
public:
	PWLVoltageSource();
	~PWLVoltageSource();
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

