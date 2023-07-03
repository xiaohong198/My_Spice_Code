#pragma once
#include "Device.h"
class Capacitor :public Device
{
private:
	double capacitance;

public:
	Capacitor();
	~Capacitor();

	void getSubB(Eigen::MatrixXd& SubB);
	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
