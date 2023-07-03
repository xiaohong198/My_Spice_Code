#pragma once
#include "SpiceDevice.h"

class SpiceDiode : public SpiceDevice
{
protected:
	//Main
	double AREA;
	double SCALE;
	double IS;
	double IKF;
	double ISR;
	double N;
	double NR;
	double M;
	double VJ;
	double RS;

	//Junction Capitance
	bool IFModelJunctionCapacitance;
	double CJO;
	double FC;
	double TT;

	bool IFSpecifyInitialCondition;
	double V0;

	//Reverse Breakdown
	bool IFModelReverseBreakdown;
	double BV;
	double IBV;
	double IBVL;
	double NBV;
	double NBVL;

	//Temperature
	double EG;//Activation energy;

	//geometry-adjusted variables and the defining equations
	double CJOd;
	double IBVd;
	double ISd;
	double RSd;

	//Thermal Voltage
	double Vt;

	//中间常量
	double F1;
	double F2;
	double F3;

	//Calculation needs
	double Ifwd;
	double DIfwdDVd;
	double Vd;

public:
	SpiceDiode();
	~SpiceDiode();

	void getSubA(Eigen::MatrixXd& subA);
	void getSubPandPJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian);
	void getSubQandQJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);
	int getReturnPrime();
	void setDeviceInfo(map<string, int>& _PortMap);
	void setInputData(InputStr _DataStr, map<string, int>& _PortMap);
	DeviceInfoStr getDeviceInfo();
	string getInstanceName();
};
