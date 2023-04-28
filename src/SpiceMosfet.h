#pragma once
#include "SpiceDevice.h"
class SpiceMosfet : public SpiceDevice
{
protected:
	double MTYPE;
	//Dimensions
	double AREA;//Device area
	double SCALE;//并联的器件数
	double LENGTH;//channel length
	double WIDTH;//channel width
	double AD;//Drain area
	double AS;//Source area
	double PD;//Drain perimeter
	double PS;//Source perimeter
	double NRD;//Number of drain diffusion resistance squares
	double NRS;//Number of transistor source diffusion squares of resistance
	double RD;//Series resistance
	double RS;//Series resistance
	double RSH;//Per square resistance

	//DC Currents
	double VTO;//Threshold voltage
	double KP;//Transconductance
	double GAMMA;// Bulk threshold
	double PHI;// Surface potential
	double LAMBDA; //Channel-length modulation
	double IS;//Bulk saturation current magnitude
	double N;//Emission coefficient
	double Vtn;//Thermal Voltage
	double JS;//Bulk junction saturation current density
	double DELTA;//Width factor
	double VMAX;//Maximum drift velocity
	double NFS;//Fast surface state density
	double ETA;//Drain-source voltage threshold
	double THETA;//Mobility dependence coefficient
	double KAPPA;//Mobility modulation coefficient

	//C-V
	int IFModelGateCapacitance;// 0 for No intrinsic capacitance; 1 for Meyer; 2 for Charge Conversation

	bool IFModelGateOverlapCapacitance;//No — Do not include gate overlap capacitance in the model. Yes — Specify the gate-source, gate-drain, and gate-bulk capacitances.
	double CGSO;//Gate-source overlap capacitance
	double CGDO;//Gate-drain overlap capacitance
	double CGBO;//Gate-bulk overlap capacitance

	bool IFModelJunctionCapacitance;//No — Do not include junction capacitance in the model.  Yes — Specify zero-bias junction capacitance, junction potential, grading coefficient, forward-bias depletion and capacitance coefficient.
	double CBD;//Zero-bias BD capacitance
	double CBS;//Zero-bias BS capacitance

	double PB;//Bulk junction potential
	double CJ;//Zero-bias bulk junction bottom capacitance per junction area
	double MJ;//Bottom grading coefficient
	double CJSW;//Zero-bias bulk junction sidewall capacitance per junction perimeter
	double MJSW;//Sidewall grading coefficient
	double FC;//Capacitance coefficient

	bool IFSpecifyInitialCondition;
	double ICVDS;//Initial Voltage for Vds
	double ICVGS;//Initial Voltage for Vgs
	double ICVBS;//Initial Voltage for Vbs

	//Process
	double TOX;//Gate oxide thickness
	double LD;//Length of lateral diffusion
	double U0;//Zero-bias surface mobility coefficient
	double NUSB;//Substrate doping
	double TPG;//Gate type: Opposite of substrate (1) (default) | Same as substrate (-1) | Aluminum (0)
	double NSS;//Surface state density
	double XJ;//Junction depth

	//Geometry-Adjusted Variables
	double KPd;
	double ISd;
	double JSd;
	double CBDd;
	double CBSd;
	double CGSOd;
	double CGDOd;
	double CGBOd;
	double CJd;
	double CJSWd;
	double RDd;
	double RSd;
	double RSHd;

	//中间常量
	double BETA;
	double EGTmeas;
	double EGT;
	double VBI;
	double CgsOverlap;
	double CgdOverlap;
	double CgbOverlap;
	double F1bottom;
	double F2bottom;
	double F3bottom;
	double F1sidewall;
	double F2sidewall;
	double F3sidewall;
	double COX;
	double Coxt;
	double VFB;
	double Vsatmin;

	//Calculation Needs
	double Vgd;
	double Vgs;
	double Vds;
	double Vbs;
	double Vbd;
	double Vgb;
	double Von;
private:
	DeviceInfoStr DeviceInfo_;
public:
	SpiceMosfet();
	~SpiceMosfet();

	//放在各种Level的Mosfet的构造函数里
	void GetGateCapacitance();
	void GetJunctionCapacitance();
	void SpecifyInitialCondition();//和Solver里的初值关联上

	//void getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::MatrixXd& subB, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);
	void getSubA(Eigen::MatrixXd& subA);
	void getSubB(Eigen::MatrixXd& SubB);
	void getSubPandPJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian);
	void getSubQandQJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian);
	void getSubC(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subC);
	int getReturnPrime();
	void setDeviceInfo_(vector<int>);
	DeviceInfoStr getDeviceInfo_();
};

