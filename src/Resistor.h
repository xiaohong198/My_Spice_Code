#pragma once
#include "Device.h"

class Resistor :public Device
{
private:
	double resistance;
public:
	Resistor();
	~Resistor();

	void setConstValue(double);

	//void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
	void getSubA(Eigen::MatrixXd& subA);
};

