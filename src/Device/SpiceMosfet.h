#pragma once
#include "SpiceDevice.h"

class SpiceMosfet : public SpiceDevice
{
protected:
	double MTYPE_;
	//Dimensions
	double AREA_;//Device area
	double SCALE_;//并联的器件数
	double LENGTH_;//channel length
	double WIDTH_;//channel width
	double AD_;//Drain area
	double AS_;//Source area
	double PD_;//Drain perimeter
	double PS_;//Source perimeter
	double NRD_;//Number of drain diffusion resistance squares
	double NRS_;//Number of transistor source diffusion squares of resistance
	double RD_;//Series resistance
	double RS_;//Series resistance
	double RSH_;//Per square resistance

	//DC Currents
	double VTO_;//Threshold voltage
	double KP_;//Transconductance
	double GAMMA_;// Bulk threshold
	double PHI_;// Surface potential
	double LAMBDA_; //Channel-length modulation
	double IS_;//Bulk saturation current magnitude
	double N_;//Emission coefficient
	double Vtn_;//Thermal Voltage
	double JS_;//Bulk junction saturation current density
	double DELTA_;//Width factor
	double VMAX_;//Maximum drift velocity
	double NFS_;//Fast surface state density
	double ETA_;//Drain-source voltage threshold
	double THETA_;//Mobility dependence coefficient
	double KAPPA_;//Mobility modulation coefficient

	//C-V
	bool if_model_gate_overlap_capacitance_;//No — Do not include gate overlap capacitance in the model. Yes — Specify the gate-source, gate-drain, and gate-bulk capacitances.
	bool if_model_junction_capacitance_;//No — Do not include junction capacitance in the model.  Yes — Specify zero-bias junction capacitance, junction potential, grading coefficient, forward-bias depletion and capacitance coefficient.
	bool if_specify_initial_condition_;
	int if_model_gate_capacitance_;// 0 for No intrinsic capacitance; 1 for Meyer; 2 for Charge Conversation

	double CGSO_;//Gate-source overlap capacitance
	double CGDO_;//Gate-drain overlap capacitance
	double CGBO_;//Gate-bulk overlap capacitance

	double CBD_;//Zero-bias BD capacitance
	double CBS_;//Zero-bias BS capacitance

	double PB_;//Bulk junction potential
	double CJ_;//Zero-bias bulk junction bottom capacitance per junction area
	double MJ_;//Bottom grading coefficient
	double CJSW_;//Zero-bias bulk junction sidewall capacitance per junction perimeter
	double MJSW_;//Sidewall grading coefficient
	double FC_;//Capacitance coefficient

	double ICVDS_;//Initial Voltage for Vds
	double ICVGS_;//Initial Voltage for Vgs
	double ICVBS_;//Initial Voltage for Vbs

	//Process
	double TOX_;//Gate oxide thickness
	double LD_;//Length of lateral diffusion
	double U0_;//Zero-bias surface mobility coefficient
	double NUSB_;//Substrate doping
	double TPG_;//Gate type: Opposite of substrate (1) (default) | Same as substrate (-1) | Aluminum (0)
	double NSS_;//Surface state density
	double XJ_;//Junction depth

	//Geometry-Adjusted Variables
	double KPd_;
	double ISd_;
	double JSd_;
	double CBDd_;
	double CBSd_;
	double CGSOd_;
	double CGDOd_;
	double CGBOd_;
	double CJd_;
	double CJSWd_;
	double RDd_;
	double RSd_;
	double RSHd_;

	//中间常量
	double BETA_;
	double EGTmeas_;
	double EGT_;
	double VBI_;
	double Cgs_Overlap_;
	double Cgd_Overlap_;
	double Cgb_Overlap_;
	double F1_bottom_;
	double F2_bottom_;
	double F3_bottom_;
	double F1_sidewall_;
	double F2_sidewall_;
	double F3_sidewall_;
	double COX_;
	double Coxt_;
	double VFB_;
	double Vsatmin_;

	//Calculation Needs
	double Vgd_;
	double Vgs_;
	double Vds_;
	double Vbs_;
	double Vbd_;
	double Vgb_;
	double Von_;

public:
	SpiceMosfet();
	~SpiceMosfet();

	//放在各种Level的Mosfet的构造函数里
	void GetGateCapacitance();
	void GetJunctionCapacitance();
	void SpecifyInitialCondition();//和Solver里的初值关联上
	void GetSubA(Eigen::MatrixXd&);
	void GetSubB(Eigen::MatrixXd&);
	void GetSubPandPJacobian(const Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&);
	void GetSubQandQJacobian(const Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&);
	void GetSubC(const Eigen::VectorXd&, Eigen::MatrixXd&);
	int GetReturnPrime();
	void SetDeviceInfo(map<string, int>&);
	void SetInputData(InputStr, map<string, int>&);
	DeviceInfoStr GetDeviceInfo();
	string GetInstanceName();
};
