#pragma once
//#include "Solver.h"
#include <Eigen/Dense>
const double PI = 3.14159265358979323846;
class Device
{
    friend class structDeviceInfo;
public:
    Device();
    ~Device();

    virtual double f(double);//只有ExcitationDevice和TimeVariantDevice会用到
    virtual double G(double);//只有TimeVariantDevice会用到
    virtual void setConstValue(double);

    virtual void getTimeInvariantSubMatrix(Eigen::MatrixXd& subA, Eigen::MatrixXd& subB);
    virtual void getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double);
    virtual void getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double, double);
    virtual void getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::MatrixXd& subB, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);

};

