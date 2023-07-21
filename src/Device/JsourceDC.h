#pragma once
#include "Device.h"
class JsourceDC :public Device
{
private:
	double j_dc_;

public:
	JsourceDC();
	~JsourceDC();

	double EFunction(double);
	double SetIntegration(double*);
	void GetSubEIntegral(Eigen::VectorXd&, double*);
	int GetReturnPrime();
	void SetDeviceInfo(map<string, int>&);
	void SetInputData(InputStr, map<string, int>&);
	DeviceInfoStr GetDeviceInfo();
	string GetInstanceName();
};
