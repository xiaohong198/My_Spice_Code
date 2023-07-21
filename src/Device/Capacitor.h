#pragma once
#include "Device.h"
class Capacitor :public Device
{
private:
	double capacitance_;

public:
	Capacitor();
	~Capacitor();

	void GetSubB(Eigen::MatrixXd&);
	int GetReturnPrime();
	void SetDeviceInfo(map<string, int>&);
	void SetInputData(InputStr, map<string, int>&);
	DeviceInfoStr GetDeviceInfo();
	string GetInstanceName();
};
