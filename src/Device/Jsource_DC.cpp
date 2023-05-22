#include "Jsource_DC.h"
Jsource_DC::Jsource_DC() {
    J_DC = 1;
}

Jsource_DC::~Jsource_DC() {

}

void Jsource_DC::setConstValue(double jdc) {
    J_DC = jdc;
}

double Jsource_DC::eFunction(double t) {
    return J_DC;
}

//void Jsource_DC::getExcitationSubMatrix(Eigen::VectorXd& subE, double t) {
//    subE.setZero();
//    subE(0) = -eFunction(t);
//    subE(1) = eFunction(t);
//}

double Jsource_DC::setIntegration(double* tList) {
    return J_DC * (tList[1] - tList[0]);
}

//void Jsource_DC::getExcitationIntegralSubMatrix(Eigen::VectorXd& subEIntegral, double t1, double t2) {
//    subEIntegral.setZero();
//    subEIntegral(0) = -setIntegration(t1, t2);
//    subEIntegral(1) = setIntegration(t1, t2);
//}

void Jsource_DC::getSubEIntegral(Eigen::VectorXd& subEIntegral, double* tList) {
    subEIntegral(0) = -setIntegration(tList);
    subEIntegral(1) = setIntegration(tList);
}