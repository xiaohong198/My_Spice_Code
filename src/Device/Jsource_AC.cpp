#include "Jsource_AC.h"
Jsource_AC::Jsource_AC() {

}

Jsource_AC::~Jsource_AC() {

}

double Jsource_AC::eFunction(double t) {
    return 10 * sin(100 * PI * t);
    //    return 100 * t;
}

double Jsource_AC::setIntegration(double* tList) {
    double t1 = tList[0];
    double t2 = tList[1];
    return 10 * (-cos(100 * PI * t2) / (100 * PI) + cos(100 * PI * t1) / (100 * PI));
    //    return 50 * (pow(t2, 2) - pow(t1, 2));
}

void Jsource_AC::getSubEIntegral(Eigen::VectorXd& subEIntegral, double* tList) {
    subEIntegral(0) = -setIntegration(tList);
    subEIntegral(1) = setIntegration(tList);
}