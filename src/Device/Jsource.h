#pragma once
#include "ExcitationDevice.h"
class Jsource :public ExcitationDevice
{
private:
	double J_DC;
public:
	Jsource();
	~Jsource();

	//void setConstValue(double);
	void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double t);
};
