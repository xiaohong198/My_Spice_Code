#pragma once
#include "Device.h"
#include <regex>

class Resistor :public Device
{
private:
	double resistance;
private:
	DeviceInfoStr DeviceInfo_;
	string InstanceName;
	InputStr InputData;

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

