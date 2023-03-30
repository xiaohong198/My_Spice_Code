#pragma once
#include "TimeInvariantDevice.h"

class Resistor :public TimeInvariantDevice
{
private:
	double resistance;
public:
	Resistor();
	~Resistor();

	void setConstValue(double);

	void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
};

