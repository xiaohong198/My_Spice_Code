#pragma once
#include "Solver.h"
#include "Device.h"
class Solver;
class Capacitor :public Device
{
private:
	double capacitance;
public:
	Capacitor();
	~Capacitor();

	void setConstValue(double);
	//void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
	void getSubB(Eigen::MatrixXd& SubB);
};

