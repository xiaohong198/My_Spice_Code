#pragma once
#include "ExcitationDevice.h"
class PWLVoltageSource:public ExcitationDevice
{
protected:
	int tCount;
	double* tList;
	double* vList;//默认按照从小到大输入

public:
	PWLVoltageSource();
	~PWLVoltageSource();
	double eFunction(double);
	void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double);

	double setIntegration(double, double);
	void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double);

};

