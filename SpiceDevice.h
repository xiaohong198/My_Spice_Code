#pragma once
#include "TimeVariantDevice.h"
#include <cmath>
class SpiceDevice: public TimeVariantDevice
{
protected://��������������һ���ļ��ȽϺã�
	double q;//elementary charge on an electron
	double k;//Boltzmann constant
	double ni;//cm^(-3)
	double epsilon0;// F/m
	double epsilonOX;//permittivity of SiO2

	double Tmeas;//������ȡ���¶ȣ�Ҳ��Tnom
	double T;//ʵ���¶�
	double Gmin;

public:
	SpiceDevice();
	~SpiceDevice();
};

