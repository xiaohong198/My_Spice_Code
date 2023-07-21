#pragma once
#include "Device.h"

class Diode :public Device
{
private:
	double is_;
	double vt_;
	double ron_;
	double vf_;
	double goff_;

public:
	Diode();
	~Diode();

	double F(double);
	double G(double);

	void GetSubPandPJacobian(const Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&);
	int GetReturnPrime();
	void SetDeviceInfo(map<string, int>&);
	void SetInputData(InputStr, map<string, int>&);
	DeviceInfoStr GetDeviceInfo();
	string GetInstanceName();
};
