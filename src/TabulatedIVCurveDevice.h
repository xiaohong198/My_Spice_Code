#pragma once
#include "Device.h"

class TabulatedIVCurveDevice :public Device
{
protected:
	int IVCount;
	double* IList;
	double* VList;//默认按照从小到大输入
	double* IDifference;//相邻两点电流差
	double* VDifference;//相邻两点电压差
	double* Coeff3;//三次项系数
	double* Coeff2;//二次项系数
	double* Coeff1;//一次项系数
	double* Coeff0;//常数项系数
public:
	TabulatedIVCurveDevice();
	~TabulatedIVCurveDevice();

	double f(double);
	double G(double);

	// virtual void setIVTable();
	void fitting(int IVCount, double* IList, double* VList, double* IDifference, double* VDifference, double* Coeff0, double* Coeff1, double* Coeff2, double* Coeff3);
	void getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::MatrixXd& subB, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);
};
