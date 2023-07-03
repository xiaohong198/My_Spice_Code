#pragma once
#include "Device.h"
class Vsource_AC :public Device
{
private:
	int PeakAmplitude;
	int Frequency;
	int PhaseShift;

public:
	Vsource_AC();
	~Vsource_AC();
	double eFunction(double);

	double setIntegration(double*);
	void getSubA(Eigen::MatrixXd& subA);
	void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);
	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
