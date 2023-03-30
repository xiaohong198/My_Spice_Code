#pragma once
#include "Solver.h"
#include "TimeInvariantDevice.h"
class Solver;
class Inductor :public TimeInvariantDevice
{
private:
	double Inductance;
public:
	Inductor();
	~Inductor();

	void setConstValue(double);
	void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
};



