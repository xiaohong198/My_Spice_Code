#pragma once
#include "SpiceDevice.h"
class SpiceMosfet : public SpiceDevice
{
protected:
	//Dimensions
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
	double JS;//Bulk junction saturation current density
	double DELTA;//Width factor
	double VMAX;//Maximum drift velocity
	double NFS;//Fast surface state density
	double ETA;//Drain-source voltage threshold
	double THETA;//Mobility dependence coefficient
	double KAPPA;//Mobility modulation coefficient

	//C-V
	int ModelGateCapacitance;// 0 for No intrinsic capacitance; 1 for Meyer; 2 for Charge Conversation

	bool ModelGateOverlapCapacitance;//No ！ Do not include gate overlap capacitance in the model. Yes ！ Specify the gate-source, gate-drain, and gate-bulk capacitances.
	double CGSO;//Gate-source overlap capacitance
	double CGDO;//Gate-drain overlap capacitance
	double CGBO;//Gate-bulk overlap capacitance

	bool ModelJunctionCapacitance;//No ！ Do not include junction capacitance in the model.  Yes ！ Specify zero-bias junction capacitance, junction potential, grading coefficient, forward-bias depletion and capacitance coefficient.
	double CBD;//Zero-bias BD capacitance
	double CBS;//Zero-bias BS capacitance

	double PB;//Bulk junction potential
	double CJ;//Zero-bias bulk junction bottom capacitance per junction area
	double MJ;//Bottom grading coefficient
	double CJSW;//Zero-bias bulk junction sidewall capacitance per junction perimeter
	double MJSW;//Sidewall grading coefficient
	double FC;//Capacitance coefficient

	bool SpecifyInitialCondition;
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

public:
	SpiceMosfet();
	~SpiceMosfet();

};

