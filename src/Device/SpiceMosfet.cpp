#include "SpiceMosfet.h"
REGISTER(SpiceMosfet);
SpiceMosfet::SpiceMosfet() {
	
}

	
void SpiceMosfet::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;

	InstanceName = _DataStr.InstanceName;

	MTYPE = stod(_DataStr.ParametersMap["MTYPE"][0]);
	AREA = stod(_DataStr.ParametersMap["AREA"][0]);
	SCALE = stod(_DataStr.ParametersMap["SCALE"][0]);
	LENGTH = stod(_DataStr.ParametersMap["LENGTH"][0]);
	WIDTH = stod(_DataStr.ParametersMap["WIDTH"][0]);
	AD = stod(_DataStr.ParametersMap["AD"][0]);
	AS = stod(_DataStr.ParametersMap["AS"][0]);
	PD = stod(_DataStr.ParametersMap["PD"][0]);
	PS = stod(_DataStr.ParametersMap["PS"][0]);
	NRD = stod(_DataStr.ParametersMap["NRD"][0]);
	NRS = stod(_DataStr.ParametersMap["NRS"][0]);
	RD = stod(_DataStr.ParametersMap["RD"][0]);
	RS = stod(_DataStr.ParametersMap["RS"][0]);
	RSH = stod(_DataStr.ParametersMap["RSH"][0]);
	VTO = stod(_DataStr.ParametersMap["VTO"][0]);
	KP = stod(_DataStr.ParametersMap["KP"][0]);
	GAMMA = stod(_DataStr.ParametersMap["GAMMA"][0]);
	PHI = stod(_DataStr.ParametersMap["PHI"][0]);
	LAMBDA = stod(_DataStr.ParametersMap["LAMBDA"][0]);
	IS = stod(_DataStr.ParametersMap["IS"][0]);
	N = stod(_DataStr.ParametersMap["N"][0]);
	JS = stod(_DataStr.ParametersMap["JS"][0]);
	IFModelGateCapacitance = stod(_DataStr.ParametersMap["IFModelGateCapacitance"][0]);
	IFModelGateOverlapCapacitance = stod(_DataStr.ParametersMap["IFModelGateOverlapCapacitance"][0]);
	CGSO = stod(_DataStr.ParametersMap["CGSO"][0]);
	CGDO = stod(_DataStr.ParametersMap["CGDO"][0]);
	CGBO = stod(_DataStr.ParametersMap["CGBO"][0]);
	IFModelJunctionCapacitance = stod(_DataStr.ParametersMap["IFModelJunctionCapacitance"][0]);
	CBD = stod(_DataStr.ParametersMap["CBD"][0]);
	CBS = stod(_DataStr.ParametersMap["CBS"][0]);
	PB = stod(_DataStr.ParametersMap["PB"][0]);
	CJ = stod(_DataStr.ParametersMap["CJ"][0]);
	MJ = stod(_DataStr.ParametersMap["MJ"][0]);
	CJSW = stod(_DataStr.ParametersMap["CJSW"][0]);
	MJSW = stod(_DataStr.ParametersMap["MJSW"][0]);
	FC = stod(_DataStr.ParametersMap["FC"][0]);
	IFSpecifyInitialCondition = stod(_DataStr.ParametersMap["IFSpecifyInitialCondition"][0]);
	ICVDS = stod(_DataStr.ParametersMap["ICVDS"][0]);
	ICVGS = stod(_DataStr.ParametersMap["ICVGS"][0]);
	ICVBS = stod(_DataStr.ParametersMap["ICVBS"][0]);
	TOX = stod(_DataStr.ParametersMap["TOX"][0]);
	LD = stod(_DataStr.ParametersMap["LD"][0]);
	U0 = stod(_DataStr.ParametersMap["U0"][0]);

	if (_DataStr.ParametersMap["NUSB"][0] == "NAN")
	{
		NUSB = NAN;
	}

	TPG = stod(_DataStr.ParametersMap["TPG"][0]);
	NSS = stod(_DataStr.ParametersMap["NSS"][0]);

	Vtn = N * k * T / q;//Thermal Voltage
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
	EGTmeas = 1.16 - (7.02 - 4 * pow(Tmeas, 2)) / (Tmeas + 1108);
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

	//Caculation Needs
	Vgd = 0;
	Vgs = 0;
	Vds = 0;
	Vbs = 0;
	Vbd = 0;
	Vgb = 0;
	Von = MTYPE * VBI;

	//端口号
	int max_port = 0;
	for (auto iter_map = _PortMap.begin(); iter_map != _PortMap.end(); iter_map++)
	{
		max_port < iter_map->second ? max_port = iter_map->second : max_port;
	}
	for (auto index_port = 0; index_port < _DataStr.Port.size(); index_port++)
	{
		if (std::regex_match(_DataStr.Port[index_port], std::regex("-?\\d+(\\.\\d*)?")))
		{
			max_port < stoi(_DataStr.Port[index_port]) ? max_port = stoi(_DataStr.Port[index_port]) : max_port;
			_PortMap.insert({ _DataStr.Port[index_port] , stoi(_DataStr.Port[index_port]) });
			// 未完成
		}
		else
		{
			if (_PortMap.find(_DataStr.Port[index_port]) != _PortMap.end())
			{
				continue;
			}
			else
			{
				_PortMap.insert({ _DataStr.Port[index_port] , ++max_port });
				//VoltageXIndex.push_back(max_port);
			}
		}
	}
	_PortMap.insert({ "- MaxPortIndex -",max_port });
	_PortMap["- MaxPortIndex -"] = max_port;
}

void SpiceMosfet::setDeviceInfo(map<string, int> &_PortMap)
{
	//DeviceInfo_.xIndex.push_back(1);
	//DeviceInfo_.xIndex.push_back(2);
	//DeviceInfo_.xIndex.push_back(3);
	//DeviceInfo_.xIndex.push_back(4);
	//DeviceInfo_.xIndex.push_back(5);
	//DeviceInfo_.xIndex.push_back(6);
	//return;
	//端口号应用
	int _max_port_index = _PortMap["- MaxPortIndex -"];
	for (auto index_port = 0; index_port < InputData.Port.size(); index_port++)
	{
		string port_name = InputData.Port[index_port];
		if (std::find(VoltageXIndex.begin(), VoltageXIndex.end(), _PortMap[port_name]) == VoltageXIndex.end())
		{
			VoltageXIndex.push_back(_PortMap[port_name]);
		}

		switch (index_port)
		{
		case 0:
			//D
			DeviceInfo_.xIndex.push_back(_PortMap[InputData.Port[0]]);
			//Dp
			DeviceInfo_.xIndex.push_back(++_max_port_index);
			VoltageXIndex.push_back(_max_port_index);
			break;
		case 1:
			//G
			DeviceInfo_.xIndex.push_back(_PortMap[InputData.Port[1]]);
			break;
		case 2:
			//B
			DeviceInfo_.xIndex.push_back(_PortMap[InputData.Port[3]]);
			break;
		case 3:
			//S
			DeviceInfo_.xIndex.push_back(_PortMap[InputData.Port[2]]);
			//Sp
			DeviceInfo_.xIndex.push_back(++_max_port_index);
			VoltageXIndex.push_back(_max_port_index);
			break;
		default:
			break;
		}
	}
	_PortMap["- MaxPortIndex -"] = _max_port_index;
}

SpiceMosfet::~SpiceMosfet() {

}


void SpiceMosfet::GetJunctionCapacitance() {

}


void SpiceMosfet::getSubA(Eigen::MatrixXd& subA) {
	subA.setZero();
	// D Dp G B S Sp ： 0 1 2 3 4 5 
	subA(0, 0) += 1 / RDd;
	subA(1, 0) += -1 / RDd;
	subA(0, 1) += -1 / RDd;
	subA(1, 1) += 1 / RDd;
	subA(4, 4) += 1 / RSd;
	subA(4, 5) += -1 / RSd;
	subA(5, 4) += -1 / RSd;
	subA(5, 5) += 1 / RSd;
}

void SpiceMosfet::getSubB(Eigen::MatrixXd& subB) {
	subB.setZero();
	subB(1, 1) += CgdOverlap;
	subB(2, 2) += CgsOverlap + CgdOverlap + CgbOverlap;
	subB(3, 3) += CgbOverlap;
	subB(5, 5) += CgsOverlap;
	subB(2, 1) += -CgdOverlap;
	subB(1, 2) += -CgdOverlap;

	subB(2, 5) += -CgsOverlap;
	subB(5, 2) += -CgsOverlap;

	subB(2, 3) += -CgbOverlap;
	subB(3, 2) += -CgbOverlap;
}

void SpiceMosfet::getSubPandPJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian) {
	subP.setZero();
	subPJacobian.setZero();
	Vgd = nodeValue(2) - nodeValue(1);//g和Dp的电压差
	Vgs = nodeValue(2) - nodeValue(5);//g和Sp
	Vds = nodeValue(1) - nodeValue(5);//Dp和Sp
	Vbs = nodeValue(3) - nodeValue(5);//B和Sp
	Vbd = nodeValue(3) - nodeValue(1);//B和Dp
	Vgb = nodeValue(2) - nodeValue(3);//G和B

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
	Von = MTYPE * VBI;//Threshold Voltage,和Vbs有关，用上一步牛顿迭代的结果估算Von的区间
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
	else {  // Vgs>Von
		if (Vds < 0) {
			//反向恢复特性
		}
		else { // Vds >=0
			if (Vds < Vgs - Von) {
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

}

void SpiceMosfet::getSubQandQJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian) {
	subQ.setZero();
	subQJacobian.setZero();
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

	subQJacobian(1, 1) += (DQbdBDVbd + DQbdSDVbd);
	subQJacobian(3, 3) += (DQbdBDVbd + DQbdSDVbd) + (DQbsBDVbs + DQbsSDVbs);//B 自电容 3个
	subQJacobian(5, 5) += (DQbsBDVbs + DQbsSDVbs);//Sp 自电容 2个
	subQJacobian(3, 1) += -(DQbdBDVbd + DQbdSDVbd);//B-Dp
	subQJacobian(1, 3) += -(DQbdBDVbd + DQbdSDVbd);

	subQJacobian(3, 5) += -(DQbsBDVbs + DQbsSDVbs);//B-Sp
	subQJacobian(5, 3) += -(DQbsBDVbs + DQbsSDVbs);

	subQ(1) += -(QbdBottom + QbdSidewall);//KCL for Dp
	subQ(3) += (QbdBottom + QbdSidewall) + (QbsBottom + QbsSidewall);//KCL for B
	subQ(5) += -(QbsBottom + QbsSidewall);//KCL for Sp
}

void SpiceMosfet::getSubC(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subC) {
	//Capacitance Model: 目前只引入了Meyer Gate Capacitance Model模型，Charge Conversation Capacitance Model待开发
	double Vth = Von;
	double CgbMeyer = 0;
	double CgdMeyer = 0;
	double CgsMeyer = 0;
	//double QgbMeyer = 0;
	//double QgdMeyer = 0;
	//double QgsMeyer = 0;
	if (Vgb < VFB) {
		CgbMeyer = Coxt;
		CgdMeyer = 0;
		CgsMeyer = 0;
		//QgbMeyer = Coxt * Vgb;
	}
	else if (Vgs < Vth) {
		CgbMeyer = Coxt / sqrt(1 + 4 / pow(GAMMA, 2) * (Vgb - VFB));
		CgdMeyer = 0;
		CgsMeyer = 0;
		//QgbMeyer = GAMMA * Coxt * sqrt(pow(GAMMA / 2, 2) + Vgb - VFB);
		//QgbMeyer = CgbMeyer * Vgb;
	}
	else if (Vgs - Vth < Vds && Vds < Vsatmin) {
		CgbMeyer = 0;
		CgdMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (1 - pow(Vsatmin, 2) / pow(2 * Vsatmin - Vds, 2));
		CgsMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (1 - pow(Vsatmin - Vds, 2) / pow(2 * Vsatmin - Vds, 2));
		//QgdMeyer = CgdMeyer * Vgd;//Cgd虽然非线性，但是和Vgd无关
		//QgsMeyer = CgsMeyer * Vgs;//Cgs虽然非线性，但是和Vgs无关
	}
	else if (Vgs - Vth < Vds && Vds >= Vsatmin) {
		CgbMeyer = 0;
		CgdMeyer = 0;
		CgsMeyer = 2.0 / 3 * (Coxt - CgbMeyer);
		//QgsMeyer = CgsMeyer * Vgs;
	}
	else if (Vgs - Vth > Vds) {
		CgbMeyer = 0;
		CgdMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (1 - pow(Vgs - Vth, 2) / pow(2 * (Vgs - Vth) - Vds, 2));
		CgsMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (1 - pow(Vgs - Vth - Vds, 2) / pow(2 * (Vgs - Vth) - Vds, 2));
		//QgdMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (Vgd + pow(Vgs - Vth, 2) / (Vgs - 2 * Vth + Vgd));
		//QgsMeyer = 2.0 / 3 * (Coxt - CgbMeyer) * (Vgs + Vds / 4 * log(abs(2 * Vgs - Vds - 2 * Vth)) - (pow(2 * Vgs - Vds - 2 * Vth, 2) - pow(Vds, 2)) / (8 * (2 * Vgs - Vds - 2 * Vth)));
		//QgdMeyer = CgdMeyer * Vgd;
		//QgsMeyer = CgsMeyer * Vgs;
	}
	subC(1, 1) += CgdMeyer;
	subC(2, 2) += CgsMeyer + CgdMeyer + CgbMeyer;
	subC(3, 3) += CgbMeyer;
	subC(5, 5) += CgsMeyer;
	subC(2, 1) += -CgdMeyer;
	subC(1, 2) += -CgdMeyer;
	   
	subC(2, 5) += -CgsMeyer;
	subC(5, 2) += -CgsMeyer;
	   
	subC(2, 3) += -CgbMeyer;
	subC(3, 2) += -CgbMeyer;
}

int SpiceMosfet::getReturnPrime()
{
	return PrimeA + PrimeB + PrimeP + PrimeQ + PrimeC;
}

DeviceInfoStr SpiceMosfet::getDeviceInfo()
{
	return DeviceInfo_;
}

string SpiceMosfet::getInstanceName()
{
	return InstanceName;
}