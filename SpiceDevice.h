#pragma once
#include "TimeVariantDevice.h"
class SpiceDevice: public TimeVariantDevice
{
protected://常数参数单独放一个文件比较好？
	double N;//Emission Coefficient
	double q;//elementary charge on an electron
	double k;//Boltzmann constant
	double ni;//cm^(-3)
	double epsilon0;// F/m
	double epsilonOX;//permittivity of SiO2

	double AREA;//Device area
	double SCALE;//并联的器件数
	double Tmeas;//参数提取的温度，也作Tnom
	double T;//实际温度

public:
	SpiceDevice();
	~SpiceDevice();

	virtual void geometryAdjustedVariables() = 0;
	virtual void temperatureDependence() = 0;

	
};

