#pragma once
#include "ExcitationDevice.h"

class Vsource_DC:public ExcitationDevice
{
private:
	double V_DC;
public:
	Vsource_DC();
	~Vsource_DC();
	void setConstValue(double);

	double eFunction(double);
	void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double);
	double setIntegration(double, double);
	void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double);
};

