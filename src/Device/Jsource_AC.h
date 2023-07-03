#pragma once
#include "Device.h"
class Jsource_AC :public Device
{
private:
	int PeakAmplitude;
	int Frequency;
	int PhaseShift;

public:
	Jsource_AC();
	~Jsource_AC();

	double eFunction(double);

	double setIntegration(double*);

	void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);

	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
