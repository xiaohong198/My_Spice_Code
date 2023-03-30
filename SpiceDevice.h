#pragma once
#include "TimeVariantDevice.h"
class SpiceDevice: public TimeVariantDevice
{
protected://��������������һ���ļ��ȽϺã�
	double N;//Emission Coefficient
	double q;//elementary charge on an electron
	double k;//Boltzmann constant
	double ni;//cm^(-3)
	double epsilon0;// F/m
	double epsilonOX;//permittivity of SiO2

	double AREA;//Device area
	double SCALE;//������������
	double Tmeas;//������ȡ���¶ȣ�Ҳ��Tnom
	double T;//ʵ���¶�

public:
	SpiceDevice();
	~SpiceDevice();

	virtual void geometryAdjustedVariables() = 0;
	virtual void temperatureDependence() = 0;

	
};

