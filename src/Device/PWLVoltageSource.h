#pragma once
#include "Device.h"

class PWLVoltageSource :public Device
{
protected:
	int t_count_;
	double* t_list_;
	double* v_list_;//默认按照从小到大输入

public:
	PWLVoltageSource();
	~PWLVoltageSource();
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
