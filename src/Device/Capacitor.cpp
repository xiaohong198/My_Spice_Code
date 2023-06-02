#include "Capacitor.h"

Capacitor::Capacitor() {
    capacitance = 1;
}

//void Capacitor::setConstValue(double c) {
//    capacitance = c;
//}

void Capacitor::getSubB(Eigen::MatrixXd& subB) {
    //subA.setZero();
    subB(0, 0) = capacitance;
    subB(0, 1) = -capacitance;
    subB(1, 0) = -capacitance;
    subB(1, 1) = capacitance;
}

Capacitor::~Capacitor() {
}
