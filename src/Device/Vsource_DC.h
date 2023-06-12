#pragma once
#include "Device.h"
#include <regex>

class Vsource_DC :public Device
{
private:
	double V_DC;
private:
	DeviceInfoStr DeviceInfo_;
	string InstanceName;
	InputStr InputData;

public:
	Vsource_DC();
	~Vsource_DC();
	double eFunction(double);
	//void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double);
	double setIntegration(double*);
	//void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double);
	void getSubA(Eigen::MatrixXd& subA);
	void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);
	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
