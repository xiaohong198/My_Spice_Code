#include "SpiceMosfet.h"
SpiceMosfet::SpiceMosfet() {
	MTYPE = 1;
	//Dimensions
	AREA = 1;
	SCALE = 1;
	LENGTH = 1e-4;//channel length
	WIDTH = 1e-4;//channel width
	AD = 0;//Drain area
	AS = 0;//Source area
	PD = 0;//Drain perimeter
	PS = 0;//Source perimeter
	NRD = 1;//Number of drain diffusion resistance squares
	NRS = 1;//Number of transistor source diffusion squares of resistance
	RD = 0.0001;//Series resistance
	RS = 0.00909126;//Series resistance
	RSH = 0;//Per square resistance

	//DC Currents
	VTO = 4.17022;//Threshold voltage
	KP = 67.7358;//Transconductance
	GAMMA = 0;// Bulk threshold
	PHI = 0.6;// Surface potential
	LAMBDA = 0.0567706; //Channel-length modulation
	IS = 1e-32;//Bulk saturation current magnitude
	N = 1;//Emission coefficient
	Vtn = N * k * T / q;//Thermal Voltage
	JS = 0;//Bulk junction saturation current density
	/*--------------Level 3 参数------------*/
	//DELTA = 0;//Width factor,Level 3 参数
	//VMAX = 0;//Maximum drift velocity，Level 3 参数
	//NFS = 0;//Fast surface state density，Level 3 参数
	//ETA = 0;//Drain-source voltage threshold，Level 3 参数
	//THETA = 0;//Mobility dependence coefficient，Level 3 参数
	//KAPPA = 0.2;//Mobility modulation coefficient，Level 3 参数
	/*-------------------------------------*/
	//C-V
	IFModelGateCapacitance = 0;// 0 for No intrinsic capacitance; 1 for Meyer; 2 for Charge Conversation

	IFModelGateOverlapCapacitance = 0;//No — Do not include gate overlap capacitance in the model. Yes — Specify the gate-source, gate-drain, and gate-bulk capacitances.
	CGSO = 1.82225e-05;//Gate-source overlap capacitance
	CGDO = 1e-11;//Gate-drain overlap capacitance
	CGBO = 0;//Gate-bulk overlap capacitance

	IFModelJunctionCapacitance = 0;//No — Do not include junction capacitance in the model.  Yes — Specify zero-bias junction capacitance, junction potential, grading coefficient, forward-bias depletion and capacitance coefficient.
	CBD = 0;//Zero-bias BD capacitance
	CBS = 0;//Zero-bias BS capacitance

	PB = 0.8;//Bulk junction potential
	CJ = 0;//Zero-bias bulk junction bottom capacitance per junction area
	MJ = 0.5;//Bottom grading coefficient
	CJSW = 0;//Zero-bias bulk junction sidewall capacitance per junction perimeter
	MJSW = 0.5;//Sidewall grading coefficient
	FC = 0.5;//Capacitance coefficient

	IFSpecifyInitialCondition = 0;
	ICVDS = 0;//Initial Voltage for Vds
	ICVGS = 0;
	ICVBS = 0;

	//Process
	TOX = 1e-7;//Gate oxide thickness
	LD = 0;//Length of lateral diffusion
	U0 = 0;//Zero-bias surface mobility coefficient
	NUSB = NAN;//Substrate doping
	TPG = 0;//Gate type: Opposite of substrate (1) (default) | Same as substrate (-1) | Aluminum (0)
	NSS = 0;//Surface state density
//	XJ = 0;//Junction depth，Level 3

	//Geometry-Adjusted Variables
	KPd = KP * AREA * SCALE;
	ISd = IS * AREA * SCALE;
	JSd = JS * AREA * SCALE;
	CBDd = CBD * AREA * SCALE;
	CBSd = CBS * AREA * SCALE;
	CGSOd = CGSO * AREA * SCALE;
	CGDOd = CGDO * AREA * SCALE;
	CGBOd = CGBO * AREA * SCALE;
	CJd = CJ * AREA * SCALE;
	CJSWd = CJSW * AREA * SCALE;
	RDd = RD / (AREA * SCALE);
	RSd = RS / (AREA * SCALE);
	RSHd = RSH / (AREA * SCALE);

	//一些中间常量
	BETA = KPd * WIDTH / (LENGTH - 2 * LD);
	EGTmeas = 1.16 - (7.02 - 4 * pow(Tmeas,2)) / (Tmeas + 1108);
	EGT = 1.16 - (7.02 - 4 * pow(T, 2)) / (T + 1108);
	VBI = VTO + MTYPE * (-GAMMA * sqrt(PHI)) + (EGTmeas - EGT) / 2;
	CgsOverlap = CGSOd * WIDTH;
	CgdOverlap = CGDOd * WIDTH;
	CgbOverlap = CGBOd * (LENGTH - 2 * LD);
	F1bottom = PB * (1 - pow(1 - FC, 1 - MJ)) / (1 - MJ);
	F2bottom = pow(1 - FC, 1 + MJ);
	F3bottom = 1 - FC * (1 + MJ);
	F1sidewall = PB * (1 - pow(1 - FC, 1 - MJSW)) / (1 - MJSW);
	F2sidewall = pow(1 - FC, 1 + MJSW);
	F3sidewall = 1 - FC * (1 + MJSW);
	COX = epsilonOX / TOX;
	Coxt = WIDTH * (LENGTH - 2 * LD) * COX * AREA * SCALE;
	VFB = VBI * MTYPE - PHI;
	Vsatmin = 1;

}

SpiceMosfet::~SpiceMosfet() {

}

//void SpiceMosfet::GetGateCapacitance() {
//	if (IFModelGateCapacitance == 0) {
//		Cgd = 0;
//		Cgs = 0;
//		Cgb = 0;
//	}
//	else if (IFModelGateCapacitance == 1) {//Meyer电容模型
//		if (Vgb < VFB)
//		if (IFModelGateOverlapCapacitance) {
//
//		}
//	}
//}

void SpiceMosfet::GetJunctionCapacitance() {

}

void SpiceMosfet::getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::MatrixXd& subB, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian) {
	subA.setZero();
	subB.setZero();
	subP.setZero();
	subPJacobian.setZero();
	subQ.setZero();
	subQJacobian.setZero();
	// D Dp G B S Sp ： 0 1 2 3 4 5 
	double Vgd = nodeValue(2) - nodeValue(1);//g和Dp的电压差
	double Vgs = nodeValue(2) - nodeValue(5);//g和Sp
	double Vds = nodeValue(1) - nodeValue(5);//Dp和Sp
	double Vbs = nodeValue(3) - nodeValue(5);//B和Sp
	double Vbd = nodeValue(3) - nodeValue(1);//B和Dp
	double Vgb = nodeValue(2) - nodeValue(3);//G和B
	subA(0, 0) += 1 / RDd;
	subA(1, 0) += -1 / RDd;
	subA(0, 1) += -1 / RDd;
	subA(1, 1) += 1 / RDd;
	subA(4, 4) += 1 / RSd;
	subA(4, 5) += -1 / RSd;
	subA(5, 4) += -1 / RSd;
	subA(5, 5) += 1 / RSd;

	//Bulk Source Diode Model
	double ISbs = 0;
	double Ibs = 0;
	double Gbs = 0;
	if (JSd != 0 && AS != 0) {
		ISbs = JSd * AS;
	}
	else {
		ISbs = ISd;
	}
	if (Vbs > 80 * Vtn) {
		Ibs = ISbs * ((Vbs / Vtn - 79) * exp(80) - 1) + Vbs * Gmin;
		Gbs = ISbs * exp(80) / Vtn + Gmin;
	}
	else {
		Ibs = ISbs * (exp(Vbs / Vtn) - 1) + Vbs * Gmin;
		Gbs = ISbs / Vtn * exp(Vbs / Vtn) + Gmin;
	}
	subPJacobian(3, 3) += Gbs;
	subPJacobian(3, 5) += -Gbs;
	subPJacobian(5, 3) += -Gbs;
	subPJacobian(5, 5) += Gbs;
	subP(3) += Ibs;
	subP(5) += -Ibs;

	//Bulk Drain Diode Model
	double ISbd = 0;
	double Ibd = 0;
	double Gbd = 0;
	if (JSd != 0 && AD != 0) {
		ISbd = JSd * AD;
	}
	else {
		ISbd = ISd;
	}
	if (Vbd > 80 * Vtn) {
		Ibd = ISbd * ((Vbd / Vtn - 79) * exp(80) - 1) + Vbd * Gmin;
		Gbd = ISbd * exp(80) / Vtn + Gmin;
	}
	else {
		Ibd = ISbd * (exp(Vbd / Vtn) - 1) + Vbd * Gmin;
		Gbd = ISbd / Vtn * exp(Vbd / Vtn) + Gmin;
	}
	subPJacobian(3, 3) += Gbd;
	subPJacobian(3, 1) += -Gbd;
	subPJacobian(1, 3) += -Gbd;
	subPJacobian(1, 1) += Gbd;
	subP(3) += Ibd;
	subP(1) += -Ibd;

	//Level1 Drain Current Model
	double Von = MTYPE * VBI;//Threshold Voltage,和Vbs有关，用上一步牛顿迭代的结果估算Von的区间
	double DVonDVbs = 0;
	double Ids = 0;
	double DIdsDVgs = 0;
	double DIdsDVds = 0;
	double DIdsDVon = 0;

	if (Vbs <= 0) {
		/*Von = MTYPE * VBI + GAMMA * sqrt(PHI - Vbs);
		DVonDVbs = -1.0 / 2 * GAMMA / sqrt(PHI - Vbs);*/
		double temp1 = sqrt(PHI - Vbs);
		Von += GAMMA * temp1;
		DVonDVbs = -0.5 * GAMMA / temp1;
	}
	else if (Vbs <= 2 * PHI) {
		/*Von = MTYPE * VBI + GAMMA * (sqrt(PHI) - Vbs / (2 * sqrt(PHI)));
		DVonDVbs = -GAMMA / (2 * sqrt(PHI));*/
		double temp2 = sqrt(PHI);
		Von += GAMMA * (temp2 - Vbs / (2 * temp2));
		DVonDVbs = -GAMMA / (2 * temp2);
	}
	//else if (Vbs > 2 * PHI) {
	//	Von = MTYPE * VBI;
	//}
	//Ids=f(Vg,Vs,Vd,Vb)
	if (Vgs <= Von) {
		Ids = 0;	
	}
	else{  // Vgs>Von
		if (Vds < 0) {
			//反向恢复特性
		}
		else { // Vds >=0
			if ( Vds < Vgs - Von) {
				Ids = BETA * Vds * ((Vgs - Von) - Vds / 2) * (1 + LAMBDA * Vds);
				DIdsDVgs = BETA * Vds * (1 + LAMBDA * Vds);
				DIdsDVds = -BETA / 2 * Vds * (1 + LAMBDA * Vds) + BETA * (Vgs - Von - Vds / 2) * (1 + 2 * LAMBDA * Vds);
				DIdsDVon = -BETA * Vds * (1 + LAMBDA * Vds);
			}
			else {
				Ids = BETA * pow((Vgs - Von), 2) * (1 + LAMBDA * Vds) / 2;
				DIdsDVgs = BETA * 2 * (Vgs - Von) * (1 + LAMBDA * Vds) / 2;
				DIdsDVds = BETA * pow((Vgs - Von), 2) * LAMBDA / 2;
				DIdsDVon = -2 * BETA * (Vgs - Von) * (1 + LAMBDA * Vds) / 2;
			}
		}
		
	} 
	//Ids出现在Dp和Sp的KCL方程里
	subPJacobian(1, 2) += DIdsDVgs;//Dp点的KCL：Ids对Vg的偏导
	subPJacobian(1, 5) += -DIdsDVgs - DIdsDVds - DIdsDVon * DVonDVbs;//Dp点的KCL: Ids对VSp的偏导
	subPJacobian(1, 1) += DIdsDVds;//Ids对VDp的偏导
	subPJacobian(1, 3) += DIdsDVon * DVonDVbs;//Ids对Vb的偏导

	subPJacobian(5, 2) += -DIdsDVgs;//Sp点的KCL：-Ids对Vg的偏导
	subPJacobian(5, 5) += DIdsDVgs + DIdsDVds + DIdsDVon * DVonDVbs;//Sp点的KCL: -Ids对VSp的偏导
	subPJacobian(5, 1) += -DIdsDVds;//-Ids对VDp的偏导
	subPJacobian(5, 3) += -DIdsDVon * DVonDVbs;//-Ids对Vb的偏导

	subP(1) += Ids;
	subP(5) += -Ids;

	//Capacitance Model: 目前只引入了Meyer Gate Capacitance Model模型，Charge Conversation Capacitance Model待开发
	double Vth = Von;
	double CgbMeyer = 0;
	double CgdMeyer = 0;
	double CgsMeyer = 0;
	double QgbMeyer = 0;
	double QgdMeyer = 0;
	double QgsMeyer = 0;
	if (Vgb < VFB) {
		CgbMeyer = Coxt;
		CgdMeyer = 0;
		CgsMeyer = 0;
		QgbMeyer = Coxt * Vgb;
	}
	else if (Vgs < Vth) {
		CgbMeyer = Coxt / sqrt(1 + 4 / pow(GAMMA, 2) * (Vgb - VFB));
		CgdMeyer = 0;
		CgsMeyer = 0;
		QgbMeyer = GAMMA * Coxt * sqrt(pow(GAMMA / 2, 2) + Vgb - VFB);
	}
	else if (Vgs - Vth < Vds && Vds < Vsatmin) {
		CgbMeyer = 0;
		CgdMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (1 - pow(Vsatmin, 2) / pow(2 * Vsatmin - Vds, 2));
		CgsMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (1 - pow(Vsatmin - Vds, 2) / pow(2 * Vsatmin - Vds, 2));
		QgdMeyer = CgdMeyer * Vgd;//Cgd虽然非线性，但是和Vgd无关
		QgsMeyer = CgsMeyer * Vgs;//Cgs虽然非线性，但是和Vgs无关
	}
	else if (Vgs - Vth < Vds && Vds >= Vsatmin) {
		CgbMeyer = 0;
		CgdMeyer = 0;
		CgsMeyer = 2.0 / 3 * (Coxt - CgbMeyer);
		QgsMeyer = CgsMeyer * Vgs;
	}
	else if (Vgs - Vth > Vds) {
		CgbMeyer = 0;
		CgdMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (1 - pow(Vgs - Vth, 2) / pow(2 * (Vgs - Vth) - Vds, 2));
		CgsMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (1 - pow(Vgs - Vth - Vds, 2) / pow(2 * (Vgs - Vth) - Vds, 2));
		//QgdMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (Vgd + pow(Vgs - Vth, 2) / (Vgs - 2 * Vth + Vgd));
		//QgsMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (Vgs + Vds / 4 * log(abs(2 * Vgs - Vds - 2 * Vth)) - (pow(2 * Vgs - Vds - 2 * Vth, 2) - pow(Vds, 2)) / (8 * (2 * Vgs - Vds - 2 * Vth)));
		QgdMeyer = CgdMeyer * Vgd;
		QgsMeyer = CgsMeyer * Vgs;
	}

	/*Junction Charge Model：以下两部分组成
	* Overlap Capacitance: CGSO、CGDO、CGBO (已在构造函数里计算)
	* Bulk Junction: Bottom + SideWall ：CBD、CBS
	*/
	//B-Dp Bottom
	double QbdBottom = 0;
	double DQbdBDVbd = 0;
	if (Vbd < FC * PB)
		if (CBDd > 0) {
			QbdBottom = CBDd * PB * (1 - pow(1 - Vbd / PB, 1 - MJ)) / (1 - MJ);
			DQbdBDVbd = CBDd * pow(1 - Vbd / PB, -MJ);
		}
		else {
			QbdBottom = CJd * AD * PB * (1 - pow(1 - Vbd / PB, 1 - MJ)) / (1 - MJ);
			DQbdBDVbd = CJd * AD * pow(1 - Vbd / PB, -MJ);
		}
	else if (Vbd >= FC * PB)
		if (CBDd > 0) {
			QbdBottom = CBDd * (F1bottom + (F3bottom * (Vbd - FC * PB) + MJ * (pow(Vbd, 2) - pow((FC - PB), 2)) / (2 * PB)) / F2bottom);
			DQbdBDVbd = CBDd / F2bottom * (F3bottom + MJ / PB * Vbd);
		}
		else {
			QbdBottom = CJd * AD * (F1bottom + (F3bottom * (Vbd - FC * PB) + MJ * (pow(Vbd, 2) - pow((FC - PB), 2)) / (2 * PB)) / F2bottom);
			DQbdBDVbd = CJd * AD / F2bottom * (F3bottom + MJ / PB * Vbd);
		}

	//B-Sp Bottom
	double QbsBottom = 0;
	double DQbsBDVbs = 0;
	if (Vbs < FC * PB)
		if (CBSd > 0) {
			QbsBottom = CBSd * PB * (1 - pow(1 - Vbs / PB, 1 - MJ)) / (1 - MJ);
			DQbsBDVbs = CBSd * pow(1 - Vbs / PB, -MJ);
		}
		else {
			QbsBottom = CJd * AS * PB * (1 - pow(1 - Vbs / PB, 1 - MJ)) / (1 - MJ);
			DQbsBDVbs = CJd * AS * pow(1 - Vbs / PB, -MJ);
		}
	else if (Vbs >= FC * PB)
		if (CBSd > 0) {
			QbsBottom = CBSd * (F1bottom + (F3bottom * (Vbs - FC * PB) + MJ * (pow(Vbs, 2) - pow((FC - PB), 2)) / (2 * PB)) / F2bottom);
			DQbsBDVbs = CBSd / F2bottom * (F3bottom + MJ / PB * Vbs);
		}
		else {
			QbsBottom = CJd * AS * (F1bottom + (F3bottom * (Vbs - FC * PB) + MJ * (pow(Vbs, 2) - pow((FC - PB), 2)) / (2 * PB)) / F2bottom);
			DQbsBDVbs = CJd * AS / F2bottom * (F3bottom + MJ / PB * Vbs);
		}

	//B-Dp SideWall
	double QbdSidewall = 0;
	double DQbdSDVbd = 0;
	if (Vbd < FC * PB) {
		QbdSidewall = CJSWd * PD * PB * (1 - pow(1 - Vbd / PB, 1 - MJSW)) / (1 - MJSW);
		DQbdSDVbd = CJSWd * PD * pow(1 - Vbd / PB, -MJSW);
	}
	else {
		QbdSidewall = CJSWd * PD * (F1sidewall + (F3sidewall * (Vbd - FC * PB) + MJSW * (pow(Vbd, 2) - pow(FC - PB, 2)) / (2 * PB)) / F2sidewall);
		DQbdSDVbd = CJSWd * PD / F2sidewall * (F3sidewall + MJSW / PB * Vbd);
	}

	//B-Sp SideWall
	double QbsSidewall = 0;
	double DQbsSDVbs = 0;
	if (Vbs < FC * PB) {
		QbsSidewall = CJSWd * PS * PB * (1 - pow(1 - Vbs / PB, 1 - MJSW)) / (1 - MJSW);
		DQbsSDVbs = CJSWd * PS * pow(1 - Vbs / PB, -MJSW);
	}
	else {
		QbsSidewall = CJSWd * PS * (F1sidewall + (F3sidewall * (Vbs - FC * PB) + MJSW * (pow(Vbs, 2) - pow(FC - PB, 2)) / (2 * PB)) / F2sidewall);
		DQbsSDVbs = CJSWd * PS / F2sidewall * (F3sidewall + MJSW / PB * Vbs);
	}

	subB(1, 1) += CgdOverlap;//Dp OverlapCapacitance 常数
	subB(2, 2) += CgsOverlap + CgdOverlap + CgbOverlap;
	subB(3, 3) += CgbOverlap;
	subB(5, 5) += CgsOverlap;
	subB(2, 1) += -CgdOverlap;
	subB(1, 2) += -CgdOverlap;
	subQJacobian(1, 1) += CgdMeyer + (DQbdBDVbd + DQbdSDVbd);//Dp 自电容 2个
	subQJacobian(2, 2) += CgsMeyer + CgdMeyer + CgbMeyer;//G 自电容 3个
	subQJacobian(3, 3) += (DQbdBDVbd + DQbdBDVbd) + (DQbsBDVbs + DQbsBDVbs) + CgbMeyer;//B 自电容 3个
	subQJacobian(5, 5) += CgsMeyer + (DQbsBDVbs + DQbsSDVbs);//Sp 自电容 2个
	subQJacobian(2, 1) += -CgdMeyer;//G-Dp
	subQJacobian(1, 2) += -CgdMeyer;

	subB(2, 5) += -CgsOverlap;
	subB(5, 2) += -CgsOverlap;
	subQJacobian(2, 5) += -CgsMeyer;//G-Sp
	subQJacobian(5, 2) += -CgsMeyer;

	subB(2, 3) += -CgbOverlap;
	subB(3, 2) += -CgbOverlap;
	subQJacobian(2, 3) += -CgbMeyer;//G-B
	subQJacobian(3, 2) += -CgbMeyer;

	subQJacobian(3, 1) += -(DQbdBDVbd + DQbdSDVbd);//B-Dp
	subQJacobian(1, 3) += -(DQbdBDVbd + DQbdSDVbd);

	subQJacobian(3, 5) += -(DQbsBDVbs + DQbsSDVbs);//B-Sp
	subQJacobian(5, 3) += -(DQbsBDVbs + DQbsSDVbs);

	subQ(1) += -QgdMeyer - (QbdBottom + QbdSidewall);//KCL for Dp
	subQ(2) += QgdMeyer + QgsMeyer + QgbMeyer;//KCL for G
	subQ(3) += (QbdBottom + QbdSidewall) + (QbsBottom + QbsSidewall) - QgbMeyer;//KCL for B
	subQ(5) += -QgsMeyer - (QbsBottom + QbsSidewall);//KCL for Sp
}