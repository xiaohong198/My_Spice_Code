#include <iostream>
#include "Device.h"
using namespace std;

Device::Device() {
}

double Device::f(double Vd) {
    return Vd / 1;
}

double Device::G(double Vd) {
    return 1;
}

void Device::setConstValue(double value) {

}

void Device::getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB) {

}

void Device::getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian) {

}

void Device::getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double t) {

}

void Device::getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double t1, double t2) {

}

Device::~Device() {
}