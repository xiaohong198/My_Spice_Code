#pragma once
#include "Device.h"

class Diode :public Device
{
private:
	double Is;
	double Vt;
	double Ron;
	double Vf;
	double Goff;

public:
	Diode();
	~Diode();

	double f(double);
	double G(double);

	void getSubPandPJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian);
	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
