#include "SurgeArrester.h"
REGISTER(SurgeArrester);

SurgeArrester::SurgeArrester() {
}

SurgeArrester::~SurgeArrester() {
	delete[]i_list_;
	delete[]v_list_;
	delete[]i_difference_;
	delete[]v_difference_;
	delete[]coeff_0_;
	delete[]coeff_1_;
	delete[]coeff_2_;
	delete[]coeff_3_;
}

double SurgeArrester::F(double _v) {
	if (_v < this->v_list_[0]) {
		return this->coeff_0_[0] + this->coeff_1_[0] * (_v - this->v_list_[0]) + this->coeff_2_[0] * pow(_v - this->v_list_[0], 2) + this->coeff_3_[0] * pow(_v - this->v_list_[0], 3);
	}
	else if (_v >= this->v_list_[iv_count_ - 1]) {
		return this->coeff_0_[iv_count_ - 2] + this->coeff_1_[iv_count_ - 2] * (_v - this->v_list_[iv_count_ - 2]) + this->coeff_2_[iv_count_ - 2] * pow(_v - this->v_list_[iv_count_ - 2], 2) + this->coeff_3_[iv_count_ - 2] * pow(_v - this->v_list_[iv_count_ - 2], 3);
	}
	else {
		for (int i = 0; i < iv_count_ - 1; i++) {
			if (this->v_list_[i] <= _v && _v < this->v_list_[i + 1]) {
				return this->coeff_0_[i] + this->coeff_1_[i] * (_v - this->v_list_[i]) + this->coeff_2_[i] * pow(_v - this->v_list_[i], 2) + this->coeff_3_[i] * pow(_v - this->v_list_[i], 3);
			}
		}
		//cout << "TabulatedIVCurveDevide goes wrong!" << endl;
		//exit(0);
		return 1;
	}
}
double SurgeArrester::G(double _v) {
	if (_v < this->v_list_[0]) {
		return this->coeff_1_[0] + 2 * this->coeff_2_[0] * (_v - this->v_list_[0]) + 3 * this->coeff_3_[0] * pow(_v - this->v_list_[0], 2);
	}
	else if (_v >= this->v_list_[iv_count_ - 1]) {
		return this->coeff_1_[iv_count_ - 2] + 2 * this->coeff_2_[iv_count_ - 2] * (_v - this->v_list_[iv_count_ - 2]) + 3 * this->coeff_3_[iv_count_ - 2] * pow(_v - this->v_list_[iv_count_ - 2], 2);
	}
	else {
		for (int i = 0; i < iv_count_ - 1; i++) {
			if (this->v_list_[i] <= _v && _v < this->v_list_[i + 1]) {
				return this->coeff_1_[i] + 2 * this->coeff_2_[i] * (_v - this->v_list_[i]) + 3 * this->coeff_3_[i] * pow(_v - this->v_list_[i], 2);
			}
		}
		//cout << "TabulatedIVCurveDevide goes wrong!" << endl;
		//exit(0);
		return 1;
	}
}

void SurgeArrester::GetSubPandPJacobian(const Eigen::VectorXd& _node_value, Eigen::VectorXd& _sub_p, Eigen::MatrixXd& _sub_p_jacobian) {
	double V = _node_value(0) - _node_value(1);
	_sub_p(0) = F(V);
	_sub_p(1) = -F(V);
	_sub_p_jacobian(0, 0) = G(V);
	_sub_p_jacobian(0, 1) = -G(V);
	_sub_p_jacobian(1, 0) = -G(V);
	_sub_p_jacobian(1, 1) = G(V);
}

void SurgeArrester::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;
	instance_name_ = _data_str.instance_name;
	if (_data_str.parameters_map.find("ivList") != _data_str.parameters_map.end())
	{
		vector<string> ivList_vec = _data_str.parameters_map["ivList"];
		iv_count_ = ivList_vec.size() / 2;
		i_list_ = new double[iv_count_];
		v_list_ = new double[iv_count_];

		for (int i = 0; i < iv_count_; i++)
		{
			i_list_[i] = stod(ivList_vec[i * 2]);
			v_list_[i] = stod(ivList_vec[(i * 2) + 1]);
		}
	}
	else
	{
		iv_count_ = stod(_data_str.parameters_map["IVCount"][0]);
		vector<string> IList_vec = _data_str.parameters_map["IList"];
		vector<string> VList_vec = _data_str.parameters_map["VList"];
		i_list_ = new double[iv_count_];
		v_list_ = new double[iv_count_];

		for (int i = 0; i < iv_count_; i++)
		{
			i_list_[i] = stod(IList_vec[i]);
		}
		for (int i = 0; i < iv_count_; i++)
		{
			v_list_[i] = stod(VList_vec[i]);
		}
	}

	i_difference_ = new double[iv_count_ - 1];
	v_difference_ = new double[iv_count_ - 1];
	coeff_0_ = new double[iv_count_ - 1];
	coeff_1_ = new double[iv_count_ - 1];
	coeff_2_ = new double[iv_count_ - 1];
	coeff_3_ = new double[iv_count_ - 1];

	Fitting(iv_count_, i_list_, v_list_);

	SetPortMap(_data_str, _port_map);
}

void SurgeArrester::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, true);
}

int SurgeArrester::GetReturnPrime()
{
	return kPrimeP;
}

DeviceInfoStr SurgeArrester::GetDeviceInfo()
{
	return device_info_;
}

string SurgeArrester::GetInstanceName()
{
	return instance_name_;
}