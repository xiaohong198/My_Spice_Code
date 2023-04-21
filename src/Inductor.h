#pragma once
#include "Solver.h"
#include "Device.h"
class Solver;
class Inductor :public Device
{
private:
	double Inductance;
public:
	Inductor();
	~Inductor();

	void setConstValue(double);
//	void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
	void getSubA(Eigen::MatrixXd& subA);
	void getSubB(Eigen::MatrixXd& subB);
};



