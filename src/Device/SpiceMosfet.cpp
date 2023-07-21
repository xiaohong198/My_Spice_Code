#include "SpiceMosfet.h"
REGISTER(SpiceMosfet);
SpiceMosfet::SpiceMosfet() {
}
SpiceMosfet::~SpiceMosfet() {
}

void SpiceMosfet::GetSubA(Eigen::MatrixXd& _sub_a) {
	_sub_a.setZero();
	// D Dp G B S Sp ��0 1 2 3 4 5
	_sub_a(0, 0) += 1 / RDd_;
	_sub_a(1, 0) += -1 / RDd_;
	_sub_a(0, 1) += -1 / RDd_;
	_sub_a(1, 1) += 1 / RDd_;
	_sub_a(4, 4) += 1 / RSd_;
	_sub_a(4, 5) += -1 / RSd_;
	_sub_a(5, 4) += -1 / RSd_;
	_sub_a(5, 5) += 1 / RSd_;
}

void SpiceMosfet::GetSubB(Eigen::MatrixXd& _sub_b) {
	_sub_b.setZero();
	_sub_b(1, 1) += Cgd_Overlap_;
	_sub_b(2, 2) += Cgs_Overlap_ + Cgd_Overlap_ + Cgb_Overlap_;
	_sub_b(3, 3) += Cgb_Overlap_;
	_sub_b(5, 5) += Cgs_Overlap_;
	_sub_b(2, 1) += -Cgd_Overlap_;
	_sub_b(1, 2) += -Cgd_Overlap_;

	_sub_b(2, 5) += -Cgs_Overlap_;
	_sub_b(5, 2) += -Cgs_Overlap_;

	_sub_b(2, 3) += -Cgb_Overlap_;
	_sub_b(3, 2) += -Cgb_Overlap_;
}

void SpiceMosfet::GetSubPandPJacobian(const Eigen::VectorXd& _node_value, Eigen::VectorXd& _sub_p, Eigen::MatrixXd& _sub_p_jacobian) {
	_sub_p.setZero();
	_sub_p_jacobian.setZero();
	Vgd_ = _node_value(2) - _node_value(1);//g和Dp的电压差
	Vgs_ = _node_value(2) - _node_value(5);//g和Sp
	Vds_ = _node_value(1) - _node_value(5);//Dp和Sp
	Vbs_ = _node_value(3) - _node_value(5);//B和Sp
	Vbd_ = _node_value(3) - _node_value(1);//B和Dp
	Vgb_ = _node_value(2) - _node_value(3);//G和B

	//Bulk Source Diode Model
	double ISbs = 0;
	double Ibs = 0;
	double Gbs = 0;
	if (JSd_ != 0 && AS_ != 0) {
		ISbs = JSd_ * AS_;
	}
	else {
		ISbs = ISd_;
	}
	if (Vbs_ > 80 * Vtn_) {
		Ibs = ISbs * ((Vbs_ / Vtn_ - 79) * exp(80) - 1) + Vbs_ * gmin_;
		Gbs = ISbs * exp(80) / Vtn_ + gmin_;
	}
	else {
		Ibs = ISbs * (exp(Vbs_ / Vtn_) - 1) + Vbs_ * gmin_;
		Gbs = ISbs / Vtn_ * exp(Vbs_ / Vtn_) + gmin_;
	}
	_sub_p_jacobian(3, 3) += Gbs;
	_sub_p_jacobian(3, 5) += -Gbs;
	_sub_p_jacobian(5, 3) += -Gbs;
	_sub_p_jacobian(5, 5) += Gbs;
	_sub_p(3) += Ibs;
	_sub_p(5) += -Ibs;

	//Bulk Drain Diode Model
	double ISbd = 0;
	double Ibd = 0;
	double Gbd = 0;
	if (JSd_ != 0 && AD_ != 0) {
		ISbd = JSd_ * AD_;
	}
	else {
		ISbd = ISd_;
	}
	if (Vbd_ > 80 * Vtn_) {
		Ibd = ISbd * ((Vbd_ / Vtn_ - 79) * exp(80) - 1) + Vbd_ * gmin_;
		Gbd = ISbd * exp(80) / Vtn_ + gmin_;
	}
	else {
		Ibd = ISbd * (exp(Vbd_ / Vtn_) - 1) + Vbd_ * gmin_;
		Gbd = ISbd / Vtn_ * exp(Vbd_ / Vtn_) + gmin_;
	}
	_sub_p_jacobian(3, 3) += Gbd;
	_sub_p_jacobian(3, 1) += -Gbd;
	_sub_p_jacobian(1, 3) += -Gbd;
	_sub_p_jacobian(1, 1) += Gbd;
	_sub_p(3) += Ibd;
	_sub_p(1) += -Ibd;

	//Level1 Drain Current Model
	Von_ = MTYPE_ * VBI_;//Threshold Voltage,和Vbs有关，用上一步牛顿迭代的结果估算Von的区�?
	double DVonDVbs = 0;
	double Ids = 0;
	double DIdsDVgs = 0;
	double DIdsDVds = 0;
	double DIdsDVon = 0;

	if (Vbs_ <= 0) {
		/*Von = MTYPE * VBI + GAMMA * sqrt(PHI - Vbs);
		DVonDVbs = -1.0 / 2 * GAMMA / sqrt(PHI - Vbs);*/
		double temp1 = sqrt(PHI_ - Vbs_);
		Von_ += GAMMA_ * temp1;
		DVonDVbs = -0.5 * GAMMA_ / temp1;
	}
	else if (Vbs_ <= 2 * PHI_) {
		/*Von = MTYPE * VBI + GAMMA * (sqrt(PHI) - Vbs / (2 * sqrt(PHI)));
		DVonDVbs = -GAMMA / (2 * sqrt(PHI));*/
		double temp2 = sqrt(PHI_);
		Von_ += GAMMA_ * (temp2 - Vbs_ / (2 * temp2));
		DVonDVbs = -GAMMA_ / (2 * temp2);
	}
	//else if (Vbs > 2 * PHI) {
	//	Von = MTYPE * VBI;
	//}
	//Ids=f(Vg,Vs,Vd,Vb)
	if (Vgs_ <= Von_) {
		Ids = 0;
	}
	else {  // Vgs>Von
		if (Vds_ < 0) {
			//反向恢复特�?
		}
		else { // Vds >=0
			if (Vds_ < Vgs_ - Von_) {
				Ids = BETA_ * Vds_ * ((Vgs_ - Von_) - Vds_ / 2) * (1 + LAMBDA_ * Vds_);
				DIdsDVgs = BETA_ * Vds_ * (1 + LAMBDA_ * Vds_);
				DIdsDVds = -BETA_ / 2 * Vds_ * (1 + LAMBDA_ * Vds_) + BETA_ * (Vgs_ - Von_ - Vds_ / 2) * (1 + 2 * LAMBDA_ * Vds_);
				DIdsDVon = -BETA_ * Vds_ * (1 + LAMBDA_ * Vds_);
			}
			else {
				Ids = BETA_ * pow((Vgs_ - Von_), 2) * (1 + LAMBDA_ * Vds_) / 2;
				DIdsDVgs = BETA_ * 2 * (Vgs_ - Von_) * (1 + LAMBDA_ * Vds_) / 2;
				DIdsDVds = BETA_ * pow((Vgs_ - Von_), 2) * LAMBDA_ / 2;
				DIdsDVon = -2 * BETA_ * (Vgs_ - Von_) * (1 + LAMBDA_ * Vds_) / 2;
			}
		}
	}
	//Ids出现在Dp和Sp的KCL方程�?
	_sub_p_jacobian(1, 2) += DIdsDVgs;//Dp点的KCL：Ids对Vg的偏�?
	_sub_p_jacobian(1, 5) += -DIdsDVgs - DIdsDVds - DIdsDVon * DVonDVbs;//Dp点的KCL: Ids对VSp的偏�?
	_sub_p_jacobian(1, 1) += DIdsDVds;//Ids对VDp的偏�?
	_sub_p_jacobian(1, 3) += DIdsDVon * DVonDVbs;//Ids对Vb的偏�?

	_sub_p_jacobian(5, 2) += -DIdsDVgs;//Sp点的KCL�?Ids对Vg的偏�?
	_sub_p_jacobian(5, 5) += DIdsDVgs + DIdsDVds + DIdsDVon * DVonDVbs;//Sp点的KCL: -Ids对VSp的偏�?
	_sub_p_jacobian(5, 1) += -DIdsDVds;//-Ids对VDp的偏�?
	_sub_p_jacobian(5, 3) += -DIdsDVon * DVonDVbs;//-Ids对Vb的偏�?

	_sub_p(1) += Ids;
	_sub_p(5) += -Ids;
}

void SpiceMosfet::GetSubQandQJacobian(const Eigen::VectorXd& _node_value, Eigen::VectorXd& _sub_q, Eigen::MatrixXd& _sub_q_jacobian) {
	_sub_q.setZero();
	_sub_q_jacobian.setZero();
	/*Junction Charge Model：以下两部分组成
* Overlap Capacitance: CGSO、CGDO、CGBO (已在构造函数里计算)
* Bulk Junction: Bottom + SideWall ：CBD、CBS
*/
//B-Dp Bottom
	double QbdBottom = 0;
	double DQbdBDVbd = 0;
	if (Vbd_ < FC_ * PB_)
		if (CBDd_ > 0) {
			QbdBottom = CBDd_ * PB_ * (1 - pow(1 - Vbd_ / PB_, 1 - MJ_)) / (1 - MJ_);
			DQbdBDVbd = CBDd_ * pow(1 - Vbd_ / PB_, -MJ_);
		}
		else {
			QbdBottom = CJd_ * AD_ * PB_ * (1 - pow(1 - Vbd_ / PB_, 1 - MJ_)) / (1 - MJ_);
			DQbdBDVbd = CJd_ * AD_ * pow(1 - Vbd_ / PB_, -MJ_);
		}
	else if (Vbd_ >= FC_ * PB_)
		if (CBDd_ > 0) {
			QbdBottom = CBDd_ * (F1_bottom_ + (F3_bottom_ * (Vbd_ - FC_ * PB_) + MJ_ * (pow(Vbd_, 2) - pow((FC_ - PB_), 2)) / (2 * PB_)) / F2_bottom_);
			DQbdBDVbd = CBDd_ / F2_bottom_ * (F3_bottom_ + MJ_ / PB_ * Vbd_);
		}
		else {
			QbdBottom = CJd_ * AD_ * (F1_bottom_ + (F3_bottom_ * (Vbd_ - FC_ * PB_) + MJ_ * (pow(Vbd_, 2) - pow((FC_ - PB_), 2)) / (2 * PB_)) / F2_bottom_);
			DQbdBDVbd = CJd_ * AD_ / F2_bottom_ * (F3_bottom_ + MJ_ / PB_ * Vbd_);
		}

	//B-Sp Bottom
	double QbsBottom = 0;
	double DQbsBDVbs = 0;
	if (Vbs_ < FC_ * PB_)
		if (CBSd_ > 0) {
			QbsBottom = CBSd_ * PB_ * (1 - pow(1 - Vbs_ / PB_, 1 - MJ_)) / (1 - MJ_);
			DQbsBDVbs = CBSd_ * pow(1 - Vbs_ / PB_, -MJ_);
		}
		else {
			QbsBottom = CJd_ * AS_ * PB_ * (1 - pow(1 - Vbs_ / PB_, 1 - MJ_)) / (1 - MJ_);
			DQbsBDVbs = CJd_ * AS_ * pow(1 - Vbs_ / PB_, -MJ_);
		}
	else if (Vbs_ >= FC_ * PB_)
		if (CBSd_ > 0) {
			QbsBottom = CBSd_ * (F1_bottom_ + (F3_bottom_ * (Vbs_ - FC_ * PB_) + MJ_ * (pow(Vbs_, 2) - pow((FC_ - PB_), 2)) / (2 * PB_)) / F2_bottom_);
			DQbsBDVbs = CBSd_ / F2_bottom_ * (F3_bottom_ + MJ_ / PB_ * Vbs_);
		}
		else {
			QbsBottom = CJd_ * AS_ * (F1_bottom_ + (F3_bottom_ * (Vbs_ - FC_ * PB_) + MJ_ * (pow(Vbs_, 2) - pow((FC_ - PB_), 2)) / (2 * PB_)) / F2_bottom_);
			DQbsBDVbs = CJd_ * AS_ / F2_bottom_ * (F3_bottom_ + MJ_ / PB_ * Vbs_);
		}

	//B-Dp SideWall
	double QbdSidewall = 0;
	double DQbdSDVbd = 0;
	if (Vbd_ < FC_ * PB_) {
		QbdSidewall = CJSWd_ * PD_ * PB_ * (1 - pow(1 - Vbd_ / PB_, 1 - MJSW_)) / (1 - MJSW_);
		DQbdSDVbd = CJSWd_ * PD_ * pow(1 - Vbd_ / PB_, -MJSW_);
	}
	else {
		QbdSidewall = CJSWd_ * PD_ * (F1_sidewall_ + (F3_sidewall_ * (Vbd_ - FC_ * PB_) + MJSW_ * (pow(Vbd_, 2) - pow(FC_ - PB_, 2)) / (2 * PB_)) / F2_sidewall_);
		DQbdSDVbd = CJSWd_ * PD_ / F2_sidewall_ * (F3_sidewall_ + MJSW_ / PB_ * Vbd_);
	}

	//B-Sp SideWall
	double QbsSidewall = 0;
	double DQbsSDVbs = 0;
	if (Vbs_ < FC_ * PB_) {
		QbsSidewall = CJSWd_ * PS_ * PB_ * (1 - pow(1 - Vbs_ / PB_, 1 - MJSW_)) / (1 - MJSW_);
		DQbsSDVbs = CJSWd_ * PS_ * pow(1 - Vbs_ / PB_, -MJSW_);
	}
	else {
		QbsSidewall = CJSWd_ * PS_ * (F1_sidewall_ + (F3_sidewall_ * (Vbs_ - FC_ * PB_) + MJSW_ * (pow(Vbs_, 2) - pow(FC_ - PB_, 2)) / (2 * PB_)) / F2_sidewall_);
		DQbsSDVbs = CJSWd_ * PS_ / F2_sidewall_ * (F3_sidewall_ + MJSW_ / PB_ * Vbs_);
	}

	_sub_q_jacobian(1, 1) += (DQbdBDVbd + DQbdSDVbd);
	_sub_q_jacobian(3, 3) += (DQbdBDVbd + DQbdSDVbd) + (DQbsBDVbs + DQbsSDVbs);//B 自电�?3�?
	_sub_q_jacobian(5, 5) += (DQbsBDVbs + DQbsSDVbs);//Sp 自电�?2�?
	_sub_q_jacobian(3, 1) += -(DQbdBDVbd + DQbdSDVbd);//B-Dp
	_sub_q_jacobian(1, 3) += -(DQbdBDVbd + DQbdSDVbd);

	_sub_q_jacobian(3, 5) += -(DQbsBDVbs + DQbsSDVbs);//B-Sp
	_sub_q_jacobian(5, 3) += -(DQbsBDVbs + DQbsSDVbs);

	_sub_q(1) += -(QbdBottom + QbdSidewall);//KCL for Dp
	_sub_q(3) += (QbdBottom + QbdSidewall) + (QbsBottom + QbsSidewall);//KCL for B
	_sub_q(5) += -(QbsBottom + QbsSidewall);//KCL for Sp
}

void SpiceMosfet::GetSubC(const Eigen::VectorXd& _node_value, Eigen::MatrixXd& _sub_c) {
	//Capacitance Model: 目前只引入了Meyer Gate Capacitance Model模型，Charge Conversation Capacitance Model待开�?
	double Vth = Von_;
	double CgbMeyer = 0;
	double CgdMeyer = 0;
	double CgsMeyer = 0;
	//double QgbMeyer = 0;
	//double QgdMeyer = 0;
	//double QgsMeyer = 0;
	if (Vgb_ < VFB_) {
		CgbMeyer = Coxt_;
		CgdMeyer = 0;
		CgsMeyer = 0;
		//QgbMeyer = Coxt * Vgb;
	}
	else if (Vgs_ < Vth) {
		CgbMeyer = Coxt_ / sqrt(1 + 4 / pow(GAMMA_, 2) * (Vgb_ - VFB_));
		CgdMeyer = 0;
		CgsMeyer = 0;
		//QgbMeyer = GAMMA * Coxt * sqrt(pow(GAMMA / 2, 2) + Vgb - VFB);
		//QgbMeyer = CgbMeyer * Vgb;
	}
	else if (Vgs_ - Vth < Vds_ && Vds_ < Vsatmin_) {
		CgbMeyer = 0;
		CgdMeyer = 2.0 / 3 * (Coxt_ - CgbMeyer) * (1 - pow(Vsatmin_, 2) / pow(2 * Vsatmin_ - Vds_, 2));
		CgsMeyer = 2.0 / 3 * (Coxt_ - CgbMeyer) * (1 - pow(Vsatmin_ - Vds_, 2) / pow(2 * Vsatmin_ - Vds_, 2));
		//QgdMeyer = CgdMeyer * Vgd;//Cgd虽然非线性，但是和Vgd无关
		//QgsMeyer = CgsMeyer * Vgs;//Cgs虽然非线性，但是和Vgs无关
	}
	else if (Vgs_ - Vth < Vds_ && Vds_ >= Vsatmin_) {
		CgbMeyer = 0;
		CgdMeyer = 0;
		CgsMeyer = 2.0 / 3 * (Coxt_ - CgbMeyer);
		//QgsMeyer = CgsMeyer * Vgs;
	}
	else if (Vgs_ - Vth > Vds_) {
		CgbMeyer = 0;
		CgdMeyer = 2.0 / 3 * (Coxt_ - CgbMeyer) * (1 - pow(Vgs_ - Vth, 2) / pow(2 * (Vgs_ - Vth) - Vds_, 2));
		CgsMeyer = 2.0 / 3 * (Coxt_ - CgbMeyer) * (1 - pow(Vgs_ - Vth - Vds_, 2) / pow(2 * (Vgs_ - Vth) - Vds_, 2));
		//QgdMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (Vgd + pow(Vgs - Vth, 2) / (Vgs - 2 * Vth + Vgd));
		//QgsMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (Vgs + Vds / 4 * log(abs(2 * Vgs - Vds - 2 * Vth)) - (pow(2 * Vgs - Vds - 2 * Vth, 2) - pow(Vds, 2)) / (8 * (2 * Vgs - Vds - 2 * Vth)));
		//QgdMeyer = CgdMeyer * Vgd;
		//QgsMeyer = CgsMeyer * Vgs;
	}
	_sub_c(1, 1) += CgdMeyer;
	_sub_c(2, 2) += CgsMeyer + CgdMeyer + CgbMeyer;
	_sub_c(3, 3) += CgbMeyer;
	_sub_c(5, 5) += CgsMeyer;
	_sub_c(2, 1) += -CgdMeyer;
	_sub_c(1, 2) += -CgdMeyer;

	_sub_c(2, 5) += -CgsMeyer;
	_sub_c(5, 2) += -CgsMeyer;

	_sub_c(2, 3) += -CgbMeyer;
	_sub_c(3, 2) += -CgbMeyer;
}

void SpiceMosfet::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;

	instance_name_ = _data_str.instance_name;
	// 基类内容
	q_ = stod(_data_str.parameters_map["q"][0]);
	k_ = stod(_data_str.parameters_map["k"][0]);
	ni_ = stod(_data_str.parameters_map["ni"][0]);
	epsilon_0_ = stod(_data_str.parameters_map["epsilon0"][0]);
	epsilon_ox_ = 3.9 * epsilon_0_;//permittivity of SiO2
	tmeas_ = stod(_data_str.parameters_map["Tmeas"][0]);
	t_ = tmeas_;
	gmin_ = stod(_data_str.parameters_map["Gmin"][0]);
	// 子类内容
	MTYPE_ = stod(_data_str.parameters_map["MTYPE"][0]);
	AREA_ = stod(_data_str.parameters_map["AREA"][0]);
	SCALE_ = stod(_data_str.parameters_map["SCALE"][0]);
	LENGTH_ = stod(_data_str.parameters_map["LENGTH"][0]);
	WIDTH_ = stod(_data_str.parameters_map["WIDTH"][0]);
	AD_ = stod(_data_str.parameters_map["AD"][0]);
	AS_ = stod(_data_str.parameters_map["AS"][0]);
	PD_ = stod(_data_str.parameters_map["PD"][0]);
	PS_ = stod(_data_str.parameters_map["PS"][0]);
	NRD_ = stod(_data_str.parameters_map["NRD"][0]);
	NRS_ = stod(_data_str.parameters_map["NRS"][0]);
	RD_ = stod(_data_str.parameters_map["RD"][0]);
	RS_ = stod(_data_str.parameters_map["RS"][0]);
	RSH_ = stod(_data_str.parameters_map["RSH"][0]);
	VTO_ = stod(_data_str.parameters_map["VTO"][0]);
	KP_ = stod(_data_str.parameters_map["KP"][0]);
	GAMMA_ = stod(_data_str.parameters_map["GAMMA"][0]);
	PHI_ = stod(_data_str.parameters_map["PHI"][0]);
	LAMBDA_ = stod(_data_str.parameters_map["LAMBDA"][0]);
	IS_ = stod(_data_str.parameters_map["IS"][0]);
	N_ = stod(_data_str.parameters_map["N"][0]);
	JS_ = stod(_data_str.parameters_map["JS"][0]);
	if_model_gate_capacitance_ = stod(_data_str.parameters_map["IFModelGateCapacitance"][0]);
	if_model_gate_overlap_capacitance_ = stod(_data_str.parameters_map["IFModelGateOverlapCapacitance"][0]);
	CGSO_ = stod(_data_str.parameters_map["CGSO"][0]);
	CGDO_ = stod(_data_str.parameters_map["CGDO"][0]);
	CGBO_ = stod(_data_str.parameters_map["CGBO"][0]);
	if_model_junction_capacitance_ = stod(_data_str.parameters_map["IFModelJunctionCapacitance"][0]);
	CBD_ = stod(_data_str.parameters_map["CBD"][0]);
	CBS_ = stod(_data_str.parameters_map["CBS"][0]);
	PB_ = stod(_data_str.parameters_map["PB"][0]);
	CJ_ = stod(_data_str.parameters_map["CJ"][0]);
	MJ_ = stod(_data_str.parameters_map["MJ"][0]);
	CJSW_ = stod(_data_str.parameters_map["CJSW"][0]);
	MJSW_ = stod(_data_str.parameters_map["MJSW"][0]);
	FC_ = stod(_data_str.parameters_map["FC"][0]);
	if_specify_initial_condition_ = stod(_data_str.parameters_map["IFSpecifyInitialCondition"][0]);
	ICVDS_ = stod(_data_str.parameters_map["ICVDS"][0]);
	ICVGS_ = stod(_data_str.parameters_map["ICVGS"][0]);
	ICVBS_ = stod(_data_str.parameters_map["ICVBS"][0]);
	TOX_ = stod(_data_str.parameters_map["TOX"][0]);
	LD_ = stod(_data_str.parameters_map["LD"][0]);
	U0_ = stod(_data_str.parameters_map["U0"][0]);

	if (_data_str.parameters_map["NUSB"][0] == "NAN")
	{
		NUSB_ = NAN;
	}

	TPG_ = stod(_data_str.parameters_map["TPG"][0]);
	NSS_ = stod(_data_str.parameters_map["NSS"][0]);

	Vtn_ = N_ * k_ * t_ / q_;//Thermal Voltage
	KPd_ = KP_ * AREA_ * SCALE_;
	ISd_ = IS_ * AREA_ * SCALE_;
	JSd_ = JS_ * AREA_ * SCALE_;
	CBDd_ = CBD_ * AREA_ * SCALE_;
	CBSd_ = CBS_ * AREA_ * SCALE_;
	CGSOd_ = CGSO_ * AREA_ * SCALE_;
	CGDOd_ = CGDO_ * AREA_ * SCALE_;
	CGBOd_ = CGBO_ * AREA_ * SCALE_;
	CJd_ = CJ_ * AREA_ * SCALE_;
	CJSWd_ = CJSW_ * AREA_ * SCALE_;
	RDd_ = RD_ / (AREA_ * SCALE_);
	RSd_ = RS_ / (AREA_ * SCALE_);
	RSHd_ = RSH_ / (AREA_ * SCALE_);
	//一些中间常�?
	BETA_ = KPd_ * WIDTH_ / (LENGTH_ - 2 * LD_);
	EGTmeas_ = 1.16 - (7.02 - 4 * pow(tmeas_, 2)) / (tmeas_ + 1108);
	EGT_ = 1.16 - (7.02 - 4 * pow(t_, 2)) / (t_ + 1108);
	VBI_ = VTO_ + MTYPE_ * (-GAMMA_ * sqrt(PHI_)) + (EGTmeas_ - EGT_) / 2;
	Cgs_Overlap_ = CGSOd_ * WIDTH_;
	Cgd_Overlap_ = CGDOd_ * WIDTH_;
	Cgb_Overlap_ = CGBOd_ * (LENGTH_ - 2 * LD_);
	F1_bottom_ = PB_ * (1 - pow(1 - FC_, 1 - MJ_)) / (1 - MJ_);
	F2_bottom_ = pow(1 - FC_, 1 + MJ_);
	F3_bottom_ = 1 - FC_ * (1 + MJ_);
	F1_sidewall_ = PB_ * (1 - pow(1 - FC_, 1 - MJSW_)) / (1 - MJSW_);
	F2_sidewall_ = pow(1 - FC_, 1 + MJSW_);
	F3_sidewall_ = 1 - FC_ * (1 + MJSW_);
	COX_ = epsilon_ox_ / TOX_;
	Coxt_ = WIDTH_ * (LENGTH_ - 2 * LD_) * COX_ * AREA_ * SCALE_;
	VFB_ = VBI_ * MTYPE_ - PHI_;
	Vsatmin_ = 1;

	//Caculation Needs
	Vgd_ = 0;
	Vgs_ = 0;
	Vds_ = 0;
	Vbs_ = 0;
	Vbd_ = 0;
	Vgb_ = 0;
	Von_ = MTYPE_ * VBI_;

	SetPortMap(_data_str, _port_map);
}

void SpiceMosfet::SetDeviceInfo(map<string, int>& _port_map)
{
	//端口号应用
	int _max_port_index = _port_map["- MaxPortIndex -"];
	for (auto index_port = 0; index_port < input_data_.port.size(); index_port++)
	{
		string port_name = input_data_.port[index_port];
		if (std::find(voltage_x_index_.begin(), voltage_x_index_.end(), _port_map[port_name]) == voltage_x_index_.end())
		{
			voltage_x_index_.push_back(_port_map[port_name]);
		}

		switch (index_port)
		{
		case 0:
			//D
			device_info_.x_index.push_back(_port_map[input_data_.port[0]]);
			//Dp
			device_info_.x_index.push_back(++_max_port_index);
			voltage_x_index_.push_back(_max_port_index);
			device_info_.additional_index.push_back(_max_port_index);

			break;
		case 1:
			//G
			device_info_.x_index.push_back(_port_map[input_data_.port[1]]);
			break;
		case 2:
			//B
			device_info_.x_index.push_back(_port_map[input_data_.port[3]]);
			break;
		case 3:
			//S
			device_info_.x_index.push_back(_port_map[input_data_.port[2]]);
			//Sp
			device_info_.x_index.push_back(++_max_port_index);
			voltage_x_index_.push_back(_max_port_index);
			device_info_.additional_index.push_back(_max_port_index);

			break;
		default:
			break;
		}
	}
	_port_map["- MaxPortIndex -"] = _max_port_index;
}

int SpiceMosfet::GetReturnPrime()
{
	return kPrimeA + kPrimeB + kPrimeP + kPrimeQ + kPrimeC;
}

DeviceInfoStr SpiceMosfet::GetDeviceInfo()
{
	return device_info_;
}

string SpiceMosfet::GetInstanceName()
{
	return instance_name_;
}