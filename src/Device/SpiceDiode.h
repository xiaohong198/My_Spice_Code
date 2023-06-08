#pragma once
#include "SpiceDevice.h"
#include <Eigen/Dense>
#include <cmath>
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

public:
	SpiceDiode();
	~SpiceDiode();

	void getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::MatrixXd& subB, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);


};
