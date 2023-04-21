#pragma once
#include "Device.h"
#include <cmath>

class Vsource_AC :public Device
{
public:
	Vsource_AC();
	~Vsource_AC();
	double eFunction(double);
	//void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double);

	double setIntegration(double*);
	//void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double);
	void getSubA(Eigen::MatrixXd& subA);
	void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);
private:
	int PeakAmplitude;
	int Frequency;
	int PhaseShift;};

