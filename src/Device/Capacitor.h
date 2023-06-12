#pragma once
#include "Solver/Solver.h"
#include "Device/Device.h"
class Capacitor :public Device
{
private:
	double capacitance;
public:
	Capacitor();
	~Capacitor();

	//void setConstValue(double);
	//void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
	void getSubB(Eigen::MatrixXd& SubB);
};
