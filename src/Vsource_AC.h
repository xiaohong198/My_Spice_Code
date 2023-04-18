#pragma once
#include "ExcitationDevice.h"
#include <cmath>

class Vsource_AC :public ExcitationDevice
{
public:
	Vsource_AC();
	~Vsource_AC();
	double eFunction(double);
	void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double);

	double setIntegration(double, double);
	void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double);
private:
	int PeakAmplitude;
	int Frequency;
	int PhaseShift;
};

