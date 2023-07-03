#pragma once
#include "Device.h"
class Jsource_DC :public Device
{
private:
	double J_DC;

public:
	Jsource_DC();
	~Jsource_DC();

	double eFunction(double);
	double setIntegration(double*);
	void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);
	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
