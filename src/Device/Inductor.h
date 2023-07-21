#pragma once
#include "Device.h"
class Inductor :public Device
{
private:
	double inductance_;

public:
	Inductor();
	~Inductor();

	void GetSubA(Eigen::MatrixXd&);
	void GetSubB(Eigen::MatrixXd&);
	int GetReturnPrime();
	void SetDeviceInfo(map<string, int>&);
	void SetInputData(InputStr, map<string, int>&);
	DeviceInfoStr GetDeviceInfo();
	string GetInstanceName();
};
