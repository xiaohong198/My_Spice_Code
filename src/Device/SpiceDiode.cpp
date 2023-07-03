#include "SpiceDiode.h"
REGISTER(SpiceDiode);
SpiceDiode::SpiceDiode() {
	////Main
	//AREA = 1;//Area of the device
	//SCALE = 1;//Number of parallel connected devices
	//IS = 1e-14;//Geometry-adjusted saturation current
	//IKF = INFINITY;//the forward knee current
	//ISR = 0;//the recombination current
	//N = 1;//emission coefficient
	//NR = 2;
	//M = 0.5;//the grading coefficient
	//VJ = 1;//the junction potential
	//RS = 0.01;

	////Junction Capacitance
	//IFModelJunctionCapacitance = false;
	//CJO = 0;
	//FC = 0.5;//the forward bias depletion capacitance coefficient
	//TT = 0;//the transit time
	//IFSpecifyInitialCondition = false;
	//V0 = 0;

	////Reverse Breakdown
	//IFModelReverseBreakdown = false;
	//BV = INFINITY;
	//IBV = 1e-10;//the reverse breakdown current
	//IBVL = 0;//the low-level reverse breakdown knee current
	//NBV = 1;//the reverse breakdown emission coefficient
	//NBVL = 1;//the low-level reverse breakdown ideality factor

	////geometry-adjusted variables and the defining equations
	//CJOd = CJO * AREA * SCALE;
	//IBVd = IBV * AREA * SCALE;
	//ISd = IS * AREA * SCALE;
	//RSd = RS / (AREA * SCALE);

	////Thermal Voltage
	//Vt = N * k * T / q;

	////中间常量
	//F1 = VJ * (1 - pow(1 - FC, 1 - M)) / (1 - M);
	//F2 = pow(1 - FC, 1 + M);
	//F3 = 1 - FC * (1 + M);

	////Calculation needs
	//Ifwd = NAN;
	//DIfwdDVd = NAN;
	//Vd = 0;
}

SpiceDiode::~SpiceDiode() {
}

void SpiceDiode::getSubA(Eigen::MatrixXd& subA) {
	subA.setZero();
	// P Pp N
	subA(0, 0) += 1 / RSd;
	subA(1, 0) += -1 / RSd;
	subA(0, 1) += -1 / RSd;
	subA(1, 1) += 1 / RSd;
}

void SpiceDiode::getSubPandPJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian) {
	subP.setZero();
	subPJacobian.setZero();
	Vd = nodeValue(1) - nodeValue(2);
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

	Ifwd = Inrm * Kinj + Irec * Kgen;
	DIfwdDVd = DInrmDVd * Kinj + Inrm * DKinjDVd + DIrecDVd * Kgen + Irec * DKgenDVd;

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

	double Id = AREA * (Ifwd - Irev);
	subP(1) += Id;
	subP(2) += -Id;
	//cout << "Diode_Id = " << Id << endl;
	double Gd = AREA * (DIfwdDVd - DIrevDVd);
	subPJacobian(1, 1) += Gd;
	subPJacobian(1, 2) += -Gd;
	subPJacobian(2, 1) += -Gd;
	subPJacobian(2, 2) += Gd;
	//cout << "Diode_Gd = " << Gd << endl;
}

void SpiceDiode::getSubQandQJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian) {
	subQ.setZero();
	subQJacobian.setZero();
	/*---------------------------------*/
	Vd = nodeValue(1) - nodeValue(2);
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

	Ifwd = Inrm * Kinj + Irec * Kgen;
	DIfwdDVd = DInrmDVd * Kinj + Inrm * DKinjDVd + DIrecDVd * Kgen + Irec * DKgenDVd;
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

void SpiceDiode::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;

	InstanceName = _DataStr.InstanceName;

	// 基类内容
	q = stod(_DataStr.ParametersMap["q"][0]);
	k = stod(_DataStr.ParametersMap["k"][0]);
	ni = stod(_DataStr.ParametersMap["ni"][0]);
	epsilon0 = stod(_DataStr.ParametersMap["epsilon0"][0]);
	epsilonOX = 3.9 * epsilon0;//permittivity of SiO2
	Tmeas = stod(_DataStr.ParametersMap["Tmeas"][0]);
	T = Tmeas;
	Gmin = stod(_DataStr.ParametersMap["Gmin"][0]);
	// 子类内容
	AREA = stod(_DataStr.ParametersMap["AREA"][0]);
	SCALE = stod(_DataStr.ParametersMap["SCALE"][0]);
	IS = stod(_DataStr.ParametersMap["IS"][0]);
	if (_DataStr.ParametersMap["IKF"][0] == "NAN")
	{
		IKF = NAN;
	}
	ISR = stod(_DataStr.ParametersMap["ISR"][0]);
	N = stod(_DataStr.ParametersMap["N"][0]);
	NR = stod(_DataStr.ParametersMap["NR"][0]);
	M = stod(_DataStr.ParametersMap["M"][0]);
	VJ = stod(_DataStr.ParametersMap["VJ"][0]);
	RS = stod(_DataStr.ParametersMap["RS"][0]);
	IFModelJunctionCapacitance = stod(_DataStr.ParametersMap["IFModelJunctionCapacitance"][0]);
	CJO = stod(_DataStr.ParametersMap["CJO"][0]);
	FC = stod(_DataStr.ParametersMap["FC"][0]);
	TT = stod(_DataStr.ParametersMap["TT"][0]);
	IFSpecifyInitialCondition = stod(_DataStr.ParametersMap["IFSpecifyInitialCondition"][0]);
	V0 = stod(_DataStr.ParametersMap["V0"][0]);
	IFModelReverseBreakdown = stod(_DataStr.ParametersMap["IFModelReverseBreakdown"][0]);
	if (_DataStr.ParametersMap["BV"][0] == "NAN")
	{
		BV = NAN;
	}
	IBV = stod(_DataStr.ParametersMap["IBV"][0]);
	IBVL = stod(_DataStr.ParametersMap["IBVL"][0]);
	NBV = stod(_DataStr.ParametersMap["NBV"][0]);
	NBVL = stod(_DataStr.ParametersMap["NBVL"][0]);

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

	//Calculation needs
	Ifwd = NAN;
	DIfwdDVd = NAN;
	Vd = 0;

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

void SpiceDiode::setDeviceInfo(map<string, int>& _PortMap)
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
			//P
			DeviceInfo_.xIndex.push_back(_PortMap[InputData.Port[0]]);
			//Pp
			DeviceInfo_.xIndex.push_back(++_max_port_index);
			VoltageXIndex.push_back(_max_port_index);
			break;
		case 1:
			//N
			DeviceInfo_.xIndex.push_back(_PortMap[InputData.Port[1]]);
			break;
		default:
			break;
		}
	}
	_PortMap["- MaxPortIndex -"] = _max_port_index;
}

int SpiceDiode::getReturnPrime()
{
	return PrimeA + PrimeP + PrimeQ;
}

DeviceInfoStr SpiceDiode::getDeviceInfo()
{
	return DeviceInfo_;
}

string SpiceDiode::getInstanceName()
{
	return InstanceName;
}