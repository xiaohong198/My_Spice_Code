#include "Vsource_AC.h"
Vsource_AC::Vsource_AC() {
	PeakAmplitude = 10;
	Frequency = 50;
	PhaseShift = 0;
}
Vsource_AC::~Vsource_AC() {

}

double Vsource_AC::eFunction(double t) {
    return PeakAmplitude * sin(2 * Frequency * PI * t + PhaseShift);
//    return 100 * t;
}

void Vsource_AC::getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double t) {
    subA.setZero();
    subA(0, 2) = 1;
    subA(1, 2) = -1;
    subA(2, 0) = 1;
    subA(2, 1) = -1;
    subE.setZero();
    subE(2) = eFunction(t);
}

double Vsource_AC::setIntegration(double t1, double t2) {
    return PeakAmplitude * (-cos(2 * Frequency  * PI * t2 + PhaseShift) / (2 * Frequency  * PI) + cos(2 * Frequency  * PI * t1 + PhaseShift) / (2 * Frequency  * PI));
//    return 50 * (pow(t2, 2) - pow(t1, 2));
}

void Vsource_AC::getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double t1, double t2) {
    subA.setZero();
    subA(0, 2) = 1;
    subA(1, 2) = -1;
    subA(2, 0) = 1;
    subA(2, 1) = -1;
    subEIntegral.setZero();
    subEIntegral(2) = setIntegration(t1,t2);
}