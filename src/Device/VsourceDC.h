#pragma once
#include "Device.h"
class VsourceDC :public Device
{
private:
	double V_DC_;

public:
	VsourceDC();
	~VsourceDC();
	double EFunction(double);
	double SetIntegration(double*);
	void GetSubA(Eigen::MatrixXd&);
	void GetSubEIntegral(Eigen::VectorXd&, double*);
	int GetReturnPrime();
	void SetDeviceInfo(map<string, int>&);
	void SetInputData(InputStr, map<string, int>&);
	DeviceInfoStr GetDeviceInfo();
	string GetInstanceName();
};
