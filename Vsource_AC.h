#pragma once
#include "ExcitationDevice.h"
#include <cmath>

const double PI = 3.14159265358979323846;

class Vsource_AC :public ExcitationDevice
{
public:
	Vsource_AC();
	~Vsource_AC();
	double eFunction(double);
	void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double);

	double setIntegration(double, double);
	void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double);
};

