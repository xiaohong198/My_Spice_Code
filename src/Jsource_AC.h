#pragma once
#include "ExcitationDevice.h"
class Jsource_AC :public ExcitationDevice
{
public:
	Jsource_AC();
	~Jsource_AC();
	double eFunction(double);
	void getExcitationSubMatrix(Eigen::VectorXd& subE, double);

	double setIntegration(double, double);
	void getExcitationIntegralSubMatrix(Eigen::VectorXd& subEIntegral, double, double);
};

