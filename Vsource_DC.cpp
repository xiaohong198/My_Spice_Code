#include "Vsource_DC.h"

Vsource_DC::Vsource_DC() {
    V_DC = 1;
}

void Vsource_DC::setConstValue(double vdc) {
    V_DC = vdc;
}

void Vsource_DC::getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double t) {
    subA.setZero();
    subA(0, 2) = 1;
    subA(1, 2) = -1;
    subA(2, 0) = 1;
    subA(2, 1) = -1;
    subE.setZero();
    subE(2) = V_DC;
}

void Vsource_DC::getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double t1, double t2) {
    subA.setZero();
    subA(0, 2) = 1;
    subA(1, 2) = -1;
    subA(2, 0) = 1;
    subA(2, 1) = -1;
    subEIntegral.setZero();
    subEIntegral(2) = V_DC*(t2-t1);
}

Vsource_DC::~Vsource_DC() {
}