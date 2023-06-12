#pragma once
//#include "Solver.h"
#include <Eigen/Dense>
#include "Struct.h"
#include "Input/Factory.h"

const double PI = 3.14159265358979323846;
class Device
{
private:
	DeviceInfoStr DeviceInfo_;
	string InstanceName;
public:
	vector <int> VoltageXIndex;
	vector <int> CurrentXIndex;
	int matrixDimension;

public:
	Device();
	~Device();

	//virtual void setConstValue(double);
	virtual void getSubA(Eigen::MatrixXd& subA);
	virtual void getSubB(Eigen::MatrixXd& SubB);
	virtual void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);//传入[t1]或者[t1,t2]
	virtual void getSubPandPJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian);
	virtual void getSubQandQJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);
	virtual void getSubC(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subC);//Meyer电容
	virtual int getReturnPrime();//获取子类类型
	virtual void setDeviceInfo(map<string, int>& _PortMap);
	virtual void setInputData(InputStr _DataStr, map<string, int>& _PortData);
	virtual DeviceInfoStr getDeviceInfo();
	virtual string getInstanceName();
};
