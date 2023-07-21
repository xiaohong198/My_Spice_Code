#pragma once
#include "Device.h"

class SpiceDevice : public Device
{
protected://常数参数单独放一个文件比较好？
	double q_;//elementary charge on an electron
	double k_;//Boltzmann constant
	double ni_;//cm^(-3)
	double epsilon_0_;// F/m
	double epsilon_ox_;//permittivity of SiO2

	double tmeas_;//参数提取的温度，也作Tnom
	double t_;//实际温度
	double gmin_;

public:
	SpiceDevice();
	~SpiceDevice();
};
