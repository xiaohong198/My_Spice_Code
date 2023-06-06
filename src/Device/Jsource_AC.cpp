#include "Jsource_AC.h"
Jsource_AC::Jsource_AC() {
    PeakAmplitude = 10;
    Frequency = 50;
    PhaseShift = 0;
}

Jsource_AC::~Jsource_AC() {

}

double Jsource_AC::eFunction(double t) {
    return PeakAmplitude * sin(2 * Frequency * PI * t + PhaseShift);
}

double Jsource_AC::setIntegration(double* tList) {
    return PeakAmplitude * (-cos(2 * Frequency * PI * tList[1] + PhaseShift) / (2 * Frequency * PI) + cos(2 * Frequency * PI * tList[0] + PhaseShift) / (2 * Frequency * PI));
    //    return 50 * (pow(t2, 2) - pow(t1, 2));
}

void Jsource_AC::getSubEIntegral(Eigen::VectorXd& subEIntegral, double* tList) {
    subEIntegral(0) = -setIntegration(tList);
    subEIntegral(1) = setIntegration(tList);
}