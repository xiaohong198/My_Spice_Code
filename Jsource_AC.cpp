#include "Jsource_AC.h"
Jsource_AC::Jsource_AC() {

}

Jsource_AC::~Jsource_AC() {

}

double Jsource_AC::eFunction(double t) {
    return 10 * sin(100 * PI * t);
    //    return 100 * t;
}

void Jsource_AC::getExcitationSubMatrix(Eigen::VectorXd& subE, double t) {
    subE.setZero();
    subE(0) = -eFunction(t);
    subE(1) = eFunction(t);
}


double Jsource_AC::setIntegration(double t1, double t2) {
    return 10 * (-cos(100 * PI * t2) / (100 * PI) + cos(100 * PI * t1) / (100 * PI));
    //    return 50 * (pow(t2, 2) - pow(t1, 2));
}

void Jsource_AC::getExcitationIntegralSubMatrix(Eigen::VectorXd& subEIntegral, double t1, double t2) {
    subEIntegral.setZero();
    subEIntegral(0) = -setIntegration(t1, t2);
    subEIntegral(1) = setIntegration(t1, t2);
}