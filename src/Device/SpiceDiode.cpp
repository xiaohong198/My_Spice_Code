#include "SpiceDiode.h"
REGISTER(SpiceDiode);
SpiceDiode::SpiceDiode() {
}

SpiceDiode::~SpiceDiode() {
}

void SpiceDiode::GetSubA(Eigen::MatrixXd& _sub_a) {
	_sub_a.setZero();
	// P Pp N
	_sub_a(0, 0) += 1 / RSd_;
	_sub_a(1, 0) += -1 / RSd_;
	_sub_a(0, 1) += -1 / RSd_;
	_sub_a(1, 1) += 1 / RSd_;
}

void SpiceDiode::GetSubPandPJacobian(const Eigen::VectorXd& _node_value, Eigen::VectorXd& _sub_p, Eigen::MatrixXd& _sub_p_jacobian) {
	_sub_p.setZero();
	_sub_p_jacobian.setZero();
	Vd_ = _node_value(1) - _node_value(2);
	//Current-Voltage Equation
	double Inrm = IS_ * exp(Vd_ / (N_ * Vt_) - 1);
	double DInrmDVd = Inrm / (N_ * Vt_);

	double Kinj = 1;
	double DKinjDVd = 0;
	if (!isinf(IKF_)) {
		Kinj = sqrt(IKF_ / (IKF_ + Inrm));
		double DKinjDInrm = 0.5 / (IKF_ + Inrm) * sqrt(IKF_ / (IKF_ + Inrm));
		DKinjDVd = DKinjDInrm * DInrmDVd;
	}

	double Irec = ISR_ * exp(Vd_ / (NR_ * Vt_) - 1);
	double DIrecDVd = Irec / (NR_ * Vt_);

	double Kgen = pow(pow((1 - Vd_) / VJ_, 2) + 0.005, M_ / 2);
	double DKgenDVd = M_ / 2 * pow(pow((1 - Vd_) / VJ_, 2) + 0.005, M_ / 2 - 1) * (-2) / VJ_ * (1 - Vd_) / VJ_;

	Ifwd_ = Inrm * Kinj + Irec * Kgen;
	DIfwdDVd_ = DInrmDVd * Kinj + Inrm * DKinjDVd + DIrecDVd * Kgen + Irec * DKgenDVd;

	double Irevh = 0;
	double Irevl = 0;
	double Irev = 0;
	double DIrevDVd = 0;
	if (!isinf(BV_)) {
		Irevh = IBV_ * exp(-(Vd_ + BV_) / (NBV_ * Vt_));
		double DIrevhDVd = Irevh / (-NBV_ * Vt_);
		Irevl = IBVL_ * exp(-(Vd_ + BV_) / (NBVL_ * Vt_));
		double DIrevlDVd = Irevl / (-NBVL_ * Vt_);
		Irev = Irevh + Irevl;
		DIrevDVd = DIrevhDVd + DIrevlDVd;
	}

	double Id = AREA_ * (Ifwd_ - Irev);
	_sub_p(1) += Id;
	_sub_p(2) += -Id;
	//cout << "Diode_Id = " << Id << endl;
	double Gd = AREA_ * (DIfwdDVd_ - DIrevDVd);
	_sub_p_jacobian(1, 1) += Gd;
	_sub_p_jacobian(1, 2) += -Gd;
	_sub_p_jacobian(2, 1) += -Gd;
	_sub_p_jacobian(2, 2) += Gd;
	//cout << "Diode_Gd = " << Gd << endl;
}

void SpiceDiode::GetSubQandQJacobian(const Eigen::VectorXd& _node_value, Eigen::VectorXd& _sub_q, Eigen::MatrixXd& _sub_q_jacobian) {
	_sub_q.setZero();
	_sub_q_jacobian.setZero();
	/*---------------------------------*/
	Vd_ = _node_value(1) - _node_value(2);
	double Inrm = IS_ * exp(Vd_ / (N_ * Vt_) - 1);
	double DInrmDVd = Inrm / (N_ * Vt_);

	double Kinj = 1;
	double DKinjDVd = 0;
	if (!isinf(IKF_)) {
		Kinj = sqrt(IKF_ / (IKF_ + Inrm));
		double DKinjDInrm = 0.5 / (IKF_ + Inrm) * sqrt(IKF_ / (IKF_ + Inrm));
		DKinjDVd = DKinjDInrm * DInrmDVd;
	}

	double Irec = ISR_ * exp(Vd_ / (NR_ * Vt_) - 1);
	double DIrecDVd = Irec / (NR_ * Vt_);

	double Kgen = pow(pow((1 - Vd_) / VJ_, 2) + 0.005, M_ / 2);
	double DKgenDVd = M_ / 2 * pow(pow((1 - Vd_) / VJ_, 2) + 0.005, M_ / 2 - 1) * (-2) / VJ_ * (1 - Vd_) / VJ_;

	Ifwd_ = Inrm * Kinj + Irec * Kgen;
	DIfwdDVd_ = DInrmDVd * Kinj + Inrm * DKinjDVd + DIrecDVd * Kgen + Irec * DKgenDVd;
	//Junction Charge Model
	double Qd = 0;
	double Cd = 0;
	if (Vd_ < FC_ * VJ_) {
		Qd = TT_ * AREA_ * Ifwd_ + CJOd_ * VJ_ * (1 - pow((1 - Vd_ / VJ_), 1 - M_)) / (1 - M_);
		Cd = TT_ * AREA_ * DIfwdDVd_ + CJOd_ * pow(1 - Vd_ / VJ_, -M_);
	}
	else {
		Qd = TT_ * AREA_ * Ifwd_ + CJOd_ * (F1_ + (F3_ * (Vd_ - FC_ * VJ_) + (M_ / 2 / VJ_) * (Vd_ * Vd_ - pow(FC_ * VJ_, 2))) / F2_);
		Cd = TT_ * AREA_ * DIfwdDVd_ + CJOd_ / F2_ * (F3_ + M_ * Vd_);
	}
	_sub_q(1) += Qd;
	_sub_q(1) += -Qd;

	_sub_q_jacobian(1, 1) += Cd;
	_sub_q_jacobian(1, 2) += -Cd;
	_sub_q_jacobian(2, 1) += -Cd;
	_sub_q_jacobian(2, 2) += Cd;
}

void SpiceDiode::SetInputData(InputStr _data_str, map<string, int>& _port_map)
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
	AREA_ = stod(_data_str.parameters_map["AREA"][0]);
	SCALE_ = stod(_data_str.parameters_map["SCALE"][0]);
	IS_ = stod(_data_str.parameters_map["IS"][0]);
	if (_data_str.parameters_map["IKF"][0] == "NAN")
	{
		IKF_ = NAN;
	}
	ISR_ = stod(_data_str.parameters_map["ISR"][0]);
	N_ = stod(_data_str.parameters_map["N"][0]);
	NR_ = stod(_data_str.parameters_map["NR"][0]);
	M_ = stod(_data_str.parameters_map["M"][0]);
	VJ_ = stod(_data_str.parameters_map["VJ"][0]);
	RS_ = stod(_data_str.parameters_map["RS"][0]);
	if_model_junction_capacitance_ = stod(_data_str.parameters_map["IFModelJunctionCapacitance"][0]);
	CJO_ = stod(_data_str.parameters_map["CJO"][0]);
	FC_ = stod(_data_str.parameters_map["FC"][0]);
	TT_ = stod(_data_str.parameters_map["TT"][0]);
	if_specify_initial_condition_ = stod(_data_str.parameters_map["IFSpecifyInitialCondition"][0]);
	V0_ = stod(_data_str.parameters_map["V0"][0]);
	if_model_reverse_breakdown_ = stod(_data_str.parameters_map["IFModelReverseBreakdown"][0]);
	if (_data_str.parameters_map["BV"][0] == "NAN")
	{
		BV_ = NAN;
	}
	IBV_ = stod(_data_str.parameters_map["IBV"][0]);
	IBVL_ = stod(_data_str.parameters_map["IBVL"][0]);
	NBV_ = stod(_data_str.parameters_map["NBV"][0]);
	NBVL_ = stod(_data_str.parameters_map["NBVL"][0]);

	//geometry-adjusted variables and the defining equations
	CJOd_ = CJO_ * AREA_ * SCALE_;
	IBVd_ = IBV_ * AREA_ * SCALE_;
	ISd_ = IS_ * AREA_ * SCALE_;
	RSd_ = RS_ / (AREA_ * SCALE_);

	//Thermal Voltage
	Vt_ = N_ * k_ * t_ / q_;

	//中间常量
	F1_ = VJ_ * (1 - pow(1 - FC_, 1 - M_)) / (1 - M_);
	F2_ = pow(1 - FC_, 1 + M_);
	F3_ = 1 - FC_ * (1 + M_);

	//Calculation needs
	Ifwd_ = NAN;
	DIfwdDVd_ = NAN;
	Vd_ = 0;

	SetPortMap(_data_str, _port_map);
}

void SpiceDiode::SetDeviceInfo(map<string, int>& _port_map)
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
			//P
			device_info_.x_index.push_back(_port_map[input_data_.port[0]]);
			//Pp
			device_info_.x_index.push_back(++_max_port_index);
			voltage_x_index_.push_back(_max_port_index);
			break;
		case 1:
			//N
			device_info_.x_index.push_back(_port_map[input_data_.port[1]]);
			break;
		default:
			break;
		}
	}
	_port_map["- MaxPortIndex -"] = _max_port_index;
}

int SpiceDiode::GetReturnPrime()
{
	return kPrimeA + kPrimeP + kPrimeQ;
}

DeviceInfoStr SpiceDiode::GetDeviceInfo()
{
	return device_info_;
}

string SpiceDiode::GetInstanceName()
{
	return instance_name_;
}