#pragma once
#include "Device.h"

class Diode :public Device
{
private:
	double Is;
	double Vt;
	double Ron;
	double Vf;
	double Goff;
public:
	Diode();
	~Diode();

	double f(double);
	double G(double);

	//void setConstValue(double, double);
	void getsubP(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian);
};
