#pragma once
#include "ExcitationDevice.h"
class Jsource_DC:public ExcitationDevice
{
private:
	double J_DC;
public:
	Jsource_DC();
	~Jsource_DC();

	void setConstValue(double);

	double eFunction(double);
	void getExcitationSubMatrix(Eigen::VectorXd& subE, double t);
	double setIntegration(double, double);
	void getExcitationIntegralSubMatrix(Eigen::VectorXd& subEIntegral, double, double);
};

