#include <iostream>
#include "Resistor.h"

using namespace std;

Resistor::Resistor() {
    resistance = 1;
}

void Resistor::setConstValue(double value) {
    resistance = value;
}

void Resistor::getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB) {
    subA(0,0) = 1/resistance;
    subA(0,1) = -1/resistance;
    subA(1,0) = -1/resistance;
    subA(1,1) = 1/resistance;
    subB.setZero();
}

Resistor::~Resistor() {

}