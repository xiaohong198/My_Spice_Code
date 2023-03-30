#include "Vsource_AC.h"
Vsource_AC::Vsource_AC() {

}

Vsource_AC::~Vsource_AC() {

}

double Vsource_AC::eFunction(double t) {
    return 10 * sin(100 * PI * t);
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
    return 10 * (-cos(100 * PI * t2) / (100 * PI) + cos(100 * PI * t1) / (100 * PI));
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