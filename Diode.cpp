#include "Diode.h"
#include <cmath>
#include <iostream>
using namespace std;
Diode::Diode() {
	Is = 1.0e-12;
	Vt = 0.026;
	Ron = 0.001;
	Vf = 0.8;
}

Diode::~Diode() {

}

double Diode::f(double Vd) {
//	return Is * (exp(Vd / Vt) - 1);
//	return pow(Vd, 2);
	if (Vd > Vf)
		return (Vd - Vf) / Ron;
	else
		return 0;
}

double Diode::G(double Vd) {
//	return Is / Vt * exp(Vd / Vt);
//	return 2 * Vd;
	if (Vd > Vf)
		return 1 / Ron;
	else
		return 0;
}

//void Diode::setConstValue(double is, double vt) {
//	Is = is;
//	Vt = vt;
//}

void Diode::getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian) {
	subA.setZero();
	double Vd = nodeValue(0) - nodeValue(1);
	subP.setZero();
	subP(0) = f(Vd);
	subP(1) = -f(Vd);
	cout << "Diode subP = " << subP << endl;
	subPJacobian.setZero();
	subPJacobian(0, 0) = G(Vd);
	subPJacobian(0, 1) = -G(Vd);
	subPJacobian(1, 0) = -G(Vd);
	subPJacobian(1, 1) = G(Vd);
	subQ.setZero();
	subQJacobian.setZero();
}