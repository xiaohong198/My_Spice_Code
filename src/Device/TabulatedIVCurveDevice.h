#pragma once
#include "Device.h"

class TabulatedIVCurveDevice :public Device
{
protected:
	double* i_difference_;//�������������
	double* v_difference_;//���������ѹ��
	double* coeff_3_;//������ϵ��
	double* coeff_2_;//������ϵ��
	double* coeff_1_;//һ����ϵ��
	double* coeff_0_;//������ϵ��

public:
	TabulatedIVCurveDevice();
	~TabulatedIVCurveDevice();

	virtual void Fitting(int, double*, double*);
};
