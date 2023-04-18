#include "Jsource.h"
Jsource::Jsource() {
    J_DC = 1;
}

Jsource::~Jsource() {

}

void Jsource::setConstValue(double jdc) {
    J_DC = jdc;
}

void Jsource::getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double t) {
    subA.setZero();
    subE.setZero();
    subE(0) = -J_DC;
    subE(1) = J_DC;
}