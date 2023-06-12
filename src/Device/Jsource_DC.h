#pragma once
#include "Device.h"
class Jsource_DC :public Device
{
private:
	double J_DC;
public:
	Jsource_DC();
	~Jsource_DC();

	//void setConstValue(double);

	double eFunction(double);
	//void getExcitationSubMatrix(Eigen::VectorXd& subE, double t);
	double setIntegration(double*);
	//void getExcitationIntegralSubMatrix(Eigen::VectorXd& subEIntegral, double, double);
	void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);
};
