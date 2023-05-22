#pragma once
//#include "Solver.h"
#include <Eigen/Dense>
#include "Struct.h"
const double PI = 3.14159265358979323846;
class Device
{
    friend class structDeviceInfo;
private:
	DeviceInfoStr DeviceInfo_;

public:
    Device();
    ~Device();

    virtual void setConstValue(double);
    virtual void getSubA(Eigen::MatrixXd& subA);
    virtual void getSubB(Eigen::MatrixXd& SubB);
    virtual void getSubEIntegral(Eigen::VectorXd& subEIntegral, double*);//传入[t1]或者[t1,t2]
    virtual void getSubPandPJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian);
    virtual void getSubQandQJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);
    virtual void getSubC(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subC);//Meyer电容
	virtual int getReturnPrime();//获取子类类型
	virtual void setDeviceInfo_(vector<int>);
	virtual DeviceInfoStr getDeviceInfo_();
};

