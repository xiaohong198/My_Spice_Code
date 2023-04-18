#pragma once
#include "Device.h"

class TabulatedIVCurveDevice :public Device
{
protected:
	int IVCount;
	double* IList;
	double* VList;//Ĭ�ϰ��մ�С��������
	double* IDifference;//�������������
	double* VDifference;//���������ѹ��
	double* Coeff3;//������ϵ��
	double* Coeff2;//������ϵ��
	double* Coeff1;//һ����ϵ��
	double* Coeff0;//������ϵ��
public:
	TabulatedIVCurveDevice();
	~TabulatedIVCurveDevice();

	double f(double);
	double G(double);

	// virtual void setIVTable();
	void fitting(int IVCount, double* IList, double* VList, double* IDifference, double* VDifference, double* Coeff0, double* Coeff1, double* Coeff2, double* Coeff3);
	void getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::MatrixXd& subB, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);
};
