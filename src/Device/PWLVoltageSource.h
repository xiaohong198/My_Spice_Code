#pragma once
#include "Device.h"

class PWLVoltageSource :public Device
{
protected:
	int tCount;
	double* tList;
	double* vList;//默认按照从小到大输入

public:
	PWLVoltageSource();
	~PWLVoltageSource();
	double eFunction(double);

	double setIntegration(double*);
	void getSubA(Eigen::MatrixXd& subA);
	void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);
	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
