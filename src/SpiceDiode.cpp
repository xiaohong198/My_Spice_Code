#include "SpiceDiode.h"
SpiceDiode::SpiceDiode() {
	//Main
	AREA = 1;//Area of the device
	SCALE = 1;//Number of parallel connected devices
	IS = 1e-14;//Geometry-adjusted saturation current
	IKF = INFINITY;//the forward knee current
	ISR = 0;//the recombination current
	N = 1;//emission coefficient
	NR = 2;
	M = 0.5;//the grading coefficient
	VJ = 1;//the junction potential
	RS = 0.01;

	//Junction Capacitance
	IFModelJunctionCapacitance = false;
	CJO = 0;
	FC = 0.5;//the forward bias depletion capacitance coefficient
	TT = 0;//the transit time
	IFSpecifyInitialCondition = false;
	V0 = 0;

	//Reverse Breakdown
	IFModelReverseBreakdown = false;
	BV = INFINITY;
	IBV = 1e-10;//the reverse breakdown current
	IBVL = 0;//the low-level reverse breakdown knee current
	NBV = 1;//the reverse breakdown emission coefficient
	NBVL = 1;//the low-level reverse breakdown ideality factor

	//geometry-adjusted variables and the defining equations
	CJOd = CJO * AREA * SCALE;
	IBVd = IBV * AREA * SCALE;
	ISd = IS * AREA * SCALE;
	RSd = RS / (AREA * SCALE);

	//Thermal Voltage
	Vt = N * k * T / q;

	//中间常量
	F1 = VJ * (1 - pow(1 - FC, 1 - M)) / (1 - M);
	F2 = pow(1 - FC, 1 + M);
	F3 = 1 - FC * (1 + M);
}

SpiceDiode::~SpiceDiode() {

}

void SpiceDiode::getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::MatrixXd& subB, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian) {
	subA.setZero();
	subB.setZero();
	subP.setZero();
	subPJacobian.setZero();
	subQ.setZero();
	subQJacobian.setZero();
	double Vd = nodeValue(1) - nodeValue(2);
	subA(0, 0) += 1 / RSd;
	subA(1, 0) += -1 / RSd;
	subA(0, 1) += -1 / RSd;
	subA(1, 1) += 1 / RSd;

	//Current-Voltage Equation
	double Inrm = IS * exp(Vd / (N * Vt) - 1);
	double DInrmDVd = Inrm / (N * Vt);

	double Kinj = 1;
	double DKinjDVd = 0;
	if (!isinf(IKF)) {
		Kinj = sqrt(IKF / (IKF + Inrm));
		double DKinjDInrm = 0.5 / (IKF + Inrm) * sqrt(IKF / (IKF + Inrm));
		DKinjDVd = DKinjDInrm * DInrmDVd;
	}

	double Irec = ISR * exp(Vd / (NR * Vt) - 1);
	double DIrecDVd = Irec / (NR * Vt);

	double Kgen = pow(pow((1 - Vd) / VJ, 2) + 0.005, M / 2);
	double DKgenDVd = M / 2 * pow(pow((1 - Vd) / VJ, 2) + 0.005, M / 2 - 1) * (-2) / VJ * (1 - Vd) / VJ;

	double Ifwd = Inrm * Kinj + Irec * Kgen;
	double DIfwdDVd = DInrmDVd * Kinj + Inrm * DKinjDVd + DIrecDVd * Kgen + Irec * DKgenDVd;

	double Irevh = 0;
	double Irevl = 0;
	double Irev = 0;
	double DIrevDVd = 0;
	if (!isinf(BV)) {
		Irevh = IBV * exp(-(Vd + BV) / (NBV * Vt));
		double DIrevhDVd = Irevh / (-NBV * Vt);
		Irevl = IBVL * exp(-(Vd + BV) / (NBVL * Vt));
		double DIrevlDVd = Irevl / (-NBVL * Vt);
		Irev = Irevh + Irevl;
		DIrevDVd = DIrevhDVd + DIrevlDVd;
	}

	double Id = AREA * (Ifwd - Irevl);
	subP(1) += Id;
	subP(2) += -Id;

	double Gd = AREA * (DIfwdDVd - DIrevDVd);
	subPJacobian(1, 1) += Gd;
	subPJacobian(1, 2) += -Gd;
	subPJacobian(2, 1) += -Gd;
	subPJacobian(2, 2) += Gd;

	//Junction Charge Model
	double Qd = 0;
	double Cd = 0;
	if (Vd < FC * VJ) {
		Qd = TT * AREA * Ifwd + CJOd * VJ * (1 - pow((1 - Vd / VJ), 1 - M)) / (1 - M);
		Cd = TT * AREA * DIfwdDVd + CJOd * pow(1 - Vd / VJ, -M);
	}
	else {
		Qd = TT * AREA * Ifwd + CJOd * (F1 + (F3 * (Vd - FC * VJ) + (M / 2 / VJ) * (Vd * Vd - pow(FC * VJ, 2))) / F2);
		Cd = TT * AREA * DIfwdDVd + CJOd / F2 * (F3 + M * Vd);
	}
	subQ(1) += Qd;
	subQ(1) += -Qd;
	subQJacobian(1, 1) += Cd;
	subQJacobian(1, 2) += -Cd;
	subQJacobian(2, 1) += -Cd;
	subQJacobian(2, 2) += Cd;
}
