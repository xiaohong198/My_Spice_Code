#pragma once
#include "Device.h"

class TabulatedIVCurveDevice :public Device
{
protected:
	double* i_difference_;//相邻两点电流差
	double* v_difference_;//相邻两点电压差
	double* coeff_3_;//三次项系数
	double* coeff_2_;//二次项系数
	double* coeff_1_;//一次项系数
	double* coeff_0_;//常数项系数

public:
	TabulatedIVCurveDevice();
	~TabulatedIVCurveDevice();

	virtual void Fitting(int, double*, double*);
};
