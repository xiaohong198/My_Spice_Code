#pragma once
#include "TimeVariantDevice.h"

class Diode :public TimeVariantDevice
{
private:
	double Is;
	double Vt;
	double Ron;
	double Vf;
public:
	Diode();
	~Diode();

	double f(double);
	double G(double);

//	void setConstValue(double, double);
	void getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::MatrixXd& subB, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);
};

