#pragma once
#include "Solver/Solver.h"
#include "Device/Device.h"
#include <regex>
class Inductor :public Device
{
private:
	double Inductance;
public:
	DeviceInfoStr DeviceInfo_;
	string InstanceName;
	InputStr InputData;
public:
	Inductor();
	~Inductor();

	//void setConstValue(double);
//	void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
	void getSubA(Eigen::MatrixXd& subA);
	void getSubB(Eigen::MatrixXd& subB);
	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
