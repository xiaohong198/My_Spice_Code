#pragma once
#include "Device.h"

class Resistor :public Device
{
private:
	double resistance_;

public:
	Resistor();
	~Resistor();
	void GetSubA(Eigen::MatrixXd&);
	int GetReturnPrime();
	void SetDeviceInfo(map<string, int>&);
	void SetInputData(InputStr, map<string, int>&);
	DeviceInfoStr GetDeviceInfo();
	string GetInstanceName();
};
