#pragma once
#include "Solver.h"
#include "TimeInvariantDevice.h"
class Solver;
class Capacitor :public TimeInvariantDevice
{
private:
	double capacitance;
public:
	Capacitor();
	~Capacitor();

	void setConstValue(double);
	void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
};

