#include "SpiceDevice.h"
SpiceDevice::SpiceDevice() {
	//��������������һ���ļ��ȽϺã�
	q = 1.6021766208e-19;//elementary charge on an electron
	k = 1.380649e-23;//Boltzmann constant
	ni = 1.45e10;//cm^(-3)
	epsilon0 = 8.854214871e-12;// F/m
	epsilonOX = 3.9 * epsilon0;//permittivity of SiO2

	//�¶����Զ���ʱû�п��ǣ��������ǣ����²���Ӧ���ǲ�ͬ��������ݳ�Ա
	Tmeas = 300.15;
	T = Tmeas;
	Gmin = 1e-12;
}

SpiceDevice::~SpiceDevice() {

}