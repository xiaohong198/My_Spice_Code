#pragma once
#include "Device.h"

class ExcitationDevice :public Device
{
public:
	ExcitationDevice();
	~ExcitationDevice();

	virtual double eFunction(double) = 0;
	virtual void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double) = 0;
	virtual double setIntegration(double, double) = 0;
	virtual void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double) = 0;
};
