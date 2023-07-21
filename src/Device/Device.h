#pragma once
#include "Struct.h"
#include "Input/Factory.h"
#include <Eigen/Dense>
#include <regex>
#include <cmath>
#include <Eigen/LU>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
const double kPI = 3.14159265358979323846;
class Device
{
protected:
	DeviceInfoStr device_info_;
	string instance_name_;
	InputStr input_data_;
public:
	vector <int> voltage_x_index_;
	vector <int> current_x_index_;
	int matrix_dimension_;

public:
	Device();
	~Device();

	//virtual void setConstValue(double);
	virtual void GetSubA(Eigen::MatrixXd&);
	virtual void GetSubB(Eigen::MatrixXd&);
	virtual void GetSubEIntegral(Eigen::VectorXd&, double*);//传入[t1]或者[t1,t2]
	virtual void GetSubPandPJacobian(const Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&);
	virtual void GetSubQandQJacobian(const Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&);
	virtual void GetSubC(const Eigen::VectorXd&, Eigen::MatrixXd&);//Meyer电
	virtual int GetReturnPrime();//获取子类类型
	virtual void SetDeviceInfo(map<string, int>&);
	virtual void SetInputData(InputStr, map<string, int>&);
	virtual DeviceInfoStr GetDeviceInfo();
	virtual string GetInstanceName();
	virtual void SetPortMap(InputStr, map<string, int>&);
	virtual DeviceInfoStr SetDeviceInfoType(map<string, int>&, bool);
};
