#pragma once
#include "SpiceDevice.h"

class SpiceDiode : public SpiceDevice
{
protected:
	//Main
	double AREA_;
	double SCALE_;
	double IS_;
	double IKF_;
	double ISR_;
	double N_;
	double NR_;
	double M_;
	double VJ_;
	double RS_;

	//Junction Capitance
	bool if_model_junction_capacitance_;
	double CJO_;
	double FC_;
	double TT_;

	bool if_specify_initial_condition_;
	double V0_;

	//Reverse Breakdown
	bool if_model_reverse_breakdown_;
	double BV_;
	double IBV_;
	double IBVL_;
	double NBV_;
	double NBVL_;

	//Temperature
	double EG_;//Activation energy;

	//geometry-adjusted variables and the defining equations
	double CJOd_;
	double IBVd_;
	double ISd_;
	double RSd_;

	//Thermal Voltage
	double Vt_;

	//中间常量
	double F1_;
	double F2_;
	double F3_;

	//Calculation needs
	double Ifwd_;
	double DIfwdDVd_;
	double Vd_;

public:
	SpiceDiode();
	~SpiceDiode();

	void GetSubA(Eigen::MatrixXd&);
	void GetSubPandPJacobian(const Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&);
	void GetSubQandQJacobian(const Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&);
	int GetReturnPrime();
	void SetDeviceInfo(map<string, int>&);
	void SetInputData(InputStr, map<string, int>&);
	DeviceInfoStr GetDeviceInfo();
	string GetInstanceName();
};
