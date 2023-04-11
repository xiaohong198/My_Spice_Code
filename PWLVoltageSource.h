#pragma once
#include "ExcitationDevice.h"
class PWLVoltageSource:public ExcitationDevice
{
protected:
	int tCount;
	double* tList;
	double* vList;//Ĭ�ϰ��մ�С��������

public:
	PWLVoltageSource();
	~PWLVoltageSource();
	double eFunction(double);
	void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double);

	double setIntegration(double, double);
	void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double);

};

