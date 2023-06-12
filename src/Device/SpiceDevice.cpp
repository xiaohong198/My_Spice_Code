#include "SpiceDevice.h"
SpiceDevice::SpiceDevice() {
	//常数参数单独放一个文件比较好？
	q = 1.6021766208e-19;//elementary charge on an electron
	k = 1.380649e-23;//Boltzmann constant
	ni = 1.45e10;//cm^(-3)
	epsilon0 = 8.854214871e-12;// F/m
	epsilonOX = 3.9 * epsilon0;//permittivity of SiO2

	//温度特性都暂时没有考虑，如若考虑，以下参数应该是不同子类的数据成员
	Tmeas = 300.15;
	T = Tmeas;
	Gmin = 1e-12;
}

SpiceDevice::~SpiceDevice() {
}