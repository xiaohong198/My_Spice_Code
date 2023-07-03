#pragma once
#include "Device.h"

class Resistor :public Device
{
private:
	double resistance;

public:
	Resistor();
	~Resistor();
	void getSubA(Eigen::MatrixXd& subA);
	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
