#include "SpiceDevice.h"
SpiceDevice::SpiceDevice() {
	//常数参数单独放一个文件比较好？
	N = 1;//Emission Coefficient
	q = 1.6021766208e-19;//elementary charge on an electron
	k = 1.380649e-23;//Boltzmann constant
	ni = 1.45e10;//cm^(-3)
	epsilon0 = 8.854214871e-12;// F/m
	epsilonOX = 3.9 * epsilon0;//permittivity of SiO2

	AREA = 1;
	SCALE = 1;
	Tmeas = 300.15;
	T = Tmeas;
}

SpiceDevice::~SpiceDevice() {

}