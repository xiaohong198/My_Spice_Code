#include "Diode.h"
#include <cmath>
#include <iostream>
using namespace std;
Diode::Diode() {
	Ron = 0.001;
	Vf = 0.8;
}

Diode::~Diode() {
}

//void Diode::setConstValue(double ron, double vf) {
//	Ron = ron;
//	Vf = vf;
//}

double Diode::f(double Vd) {
	if (Vd > Vf)
		return (Vd - Vf) / Ron;
	else
		return 0;
}

double Diode::G(double Vd) {
	if (Vd > Vf)
		return 1 / Ron;
	else
		return 0;
}

void Diode::getsubP(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian) {
	double Vd = nodeValue(0) - nodeValue(1);
	subP.setZero();
	subP(0) = f(Vd);
	subP(1) = -f(Vd);
	subPJacobian.setZero();
	subPJacobian(0, 0) = G(Vd);
	subPJacobian(0, 1) = -G(Vd);
	subPJacobian(1, 0) = -G(Vd);
	subPJacobian(1, 1) = G(Vd);
}