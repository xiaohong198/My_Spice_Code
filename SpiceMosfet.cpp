#include "SpiceMosfet.h"
SpiceMosfet::SpiceMosfet() {
	//Dimensions
	LENGTH = 1e-4;//channel length
	WIDTH = 1e-4;//channel width
	AD = 0;//Drain area
	AS = 0;//Source area
	PD = 0;//Drain perimeter
	PS = 0;//Source perimeter
	NRD = 0;//Number of drain diffusion resistance squares
	NRS = 1;//Number of transistor source diffusion squares of resistance
	RD = 0;//Series resistance
	RS = 0;//Series resistance
	RSH = 0;//Per square resistance

	//DC Currents
	VTO = 0;//Threshold voltage
	KP = 2e-5;//Transconductance
	GAMMA = 0;// Bulk threshold
	PHI = 0.6;// Surface potential
	LAMBDA = 0; //Channel-length modulation
	IS = 1e-14;//Bulk saturation current magnitude
	JS = 0;//Bulk junction saturation current density
	DELTA = 0;//Width factor
	VMAX = 0;//Maximum drift velocity
	NFS = 0;//Fast surface state density
	ETA = 0;//Drain-source voltage threshold
	THETA = 0;//Mobility dependence coefficient
	KAPPA = 0.2;//Mobility modulation coefficient

	//C-V
	ModelGateCapacitance = 0;// 0 for No intrinsic capacitance; 1 for Meyer; 2 for Charge Conversation

	ModelGateOverlapCapacitance = 0;//No ！ Do not include gate overlap capacitance in the model. Yes ！ Specify the gate-source, gate-drain, and gate-bulk capacitances.
	CGSO = 0;//Gate-source overlap capacitance
	CGDO = 0;//Gate-drain overlap capacitance
	CGBO = 0;//Gate-bulk overlap capacitance

	ModelJunctionCapacitance = 0;//No ！ Do not include junction capacitance in the model.  Yes ！ Specify zero-bias junction capacitance, junction potential, grading coefficient, forward-bias depletion and capacitance coefficient.
	CBD = 0;//Zero-bias BD capacitance
	CBS = 0;//Zero-bias BS capacitance

	PB = 0.8;//Bulk junction potential
	CJ = 0;//Zero-bias bulk junction bottom capacitance per junction area
	MJ = 0.5;//Bottom grading coefficient
	CJSW = 0;//Zero-bias bulk junction sidewall capacitance per junction perimeter
	MJSW = 0.5;//Sidewall grading coefficient
	FC = 0.5;//Capacitance coefficient

	SpecifyInitialCondition = 0;
	ICVDS = 0;//Initial Voltage for Vds
	ICVGS = 0;
	ICVBS = 0;

	//Process
	TOX = 1e-7;//Gate oxide thickness
	LD = 0;//Length of lateral diffusion
	U0 = 600;//Zero-bias surface mobility coefficient
	NUSB = NAN;//Substrate doping
	TPG = 1;//Gate type: Opposite of substrate (1) (default) | Same as substrate (-1) | Aluminum (0)
	NSS = NAN;//Surface state density
	XJ = 0;//Junction depth
}

SpiceMosfet::~SpiceMosfet() {

}