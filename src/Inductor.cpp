#include "Inductor.h"
Inductor::Inductor() {
    Inductance = 1;
}

void Inductor::setConstValue(double L) {
    Inductance = L;
}

void Inductor::getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB) {
    subA.setZero();
    subA(0, 2) = 1;
    subA(1, 2) = -1;
    subA(2, 0) = -1;
    subA(2, 1) = 1;
    subB.setZero();
    subB(2, 2) = Inductance;
}

Inductor::~Inductor() {

}