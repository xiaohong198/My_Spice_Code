#pragma once
#include "Device.h"
class Jsource_AC :public Device
{
public:
	Jsource_AC();
	~Jsource_AC();

	double eFunction(double);
	//void getExcitationSubMatrix(Eigen::VectorXd& subE, double);

	double setIntegration(double*);
	//void getExcitationIntegralSubMatrix(Eigen::VectorXd& subEIntegral, double, double);
	void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);
private:
	int PeakAmplitude;
	int Frequency;
	int PhaseShift;
};

