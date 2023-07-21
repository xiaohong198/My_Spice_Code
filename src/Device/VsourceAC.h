#pragma once
#include "Device.h"
class VsourceAC :public Device
{
private:
	int peak_amplitude_;
	int frequency_;
	int phase_shift_;

public:
	VsourceAC();
	~VsourceAC();
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
