#include "PWLVoltageSource.h"
REGISTER(PWLVoltageSource);
PWLVoltageSource::PWLVoltageSource() {
}
PWLVoltageSource::~PWLVoltageSource() {
	delete[] t_list_;
	delete[] v_list_;
}

double PWLVoltageSource::EFunction(double _t) {
	if (_t < t_list_[0]) {
		return v_list_[0];
	}
	else if (_t >= t_list_[t_count_ - 1]) {
		return v_list_[t_count_ - 1];
	}
	else {
		for (int i = 1; i < t_count_; i++) {
			if (_t < t_list_[i]) {
				return ((v_list_[i] - v_list_[i - 1]) / (t_list_[i] - t_list_[i - 1]) * (_t - t_list_[i - 1]) + v_list_[i - 1]);
				break;
			}
		}
	}
	return 0;
}

double PWLVoltageSource::SetIntegration(double* _t_list) {
	double t1 = _t_list[0];
	double t2 = _t_list[1];
	double psl_integral = 0;
	double vt1 = EFunction(t1);
	double vt2 = EFunction(t2);
	//默认t1<t2;
	int locationt1 = t_count_;
	int locationt2 = t_count_;
	for (int i = 0; i < t_count_; i++) {//定位t1
		if (t1 < _t_list[i]) {
			locationt1 = i;
			break;
		}
	}
	for (int i = 0; i < t_count_; i++) {//定位t2
		if (t2 < _t_list[i]) {
			locationt2 = i;
			break;
		}
	}
	if (locationt1 == locationt2) {
		psl_integral = (vt1 + vt2) * (t2 - t1) / 2;
	}
	else {
		psl_integral += (vt1 + v_list_[locationt1]) * (_t_list[locationt1] - t1) * 0.5;
		psl_integral += (vt2 + v_list_[locationt2 - 1]) * (t2 - _t_list[locationt2 - 1]) * 0.5;
		for (int i = locationt1; i < locationt2 - 1; i++) {//如果t1和t2在相邻区间，这个循环不会运行
			psl_integral += (v_list_[i] + v_list_[i + 1]) * (_t_list[i + 1] - _t_list[i]) * 0.5;
		}
	}
	return psl_integral;
}

void PWLVoltageSource::GetSubA(Eigen::MatrixXd& _sub_a) {
	_sub_a.setZero();
	_sub_a(0, 2) = 1;
	_sub_a(1, 2) = -1;
	_sub_a(2, 0) = 1;
	_sub_a(2, 1) = -1;
}

void PWLVoltageSource::GetSubEIntegral(Eigen::VectorXd& _sub_eIntegral, double* _t_list) {
	_sub_eIntegral.setZero();
	_sub_eIntegral(2) = (EFunction(_t_list[0]) + EFunction(_t_list[1])) / 2 * (_t_list[1] - _t_list[0]);
}

void PWLVoltageSource::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;
	instance_name_ = _data_str.instance_name;
	if (_data_str.parameters_map.find("pwl") != _data_str.parameters_map.end())
	{
		vector<string> pwl_vec = _data_str.parameters_map["pwl"];
		t_count_ = pwl_vec.size() / 2;
		t_list_ = new double[t_count_];
		v_list_ = new double[t_count_];

		for (int i = 0; i < t_count_; i++)
		{
			t_list_[i] = stod(pwl_vec[i * 2]);
			v_list_[i] = stod(pwl_vec[(i * 2) + 1]);
		}
	}
	else
	{
		t_count_ = stod(_data_str.parameters_map["tCount"][0]);
		vector<string> tList_vec = _data_str.parameters_map["tList"];
		vector<string> vList_vec = _data_str.parameters_map["vList"];
		t_list_ = new double[t_count_];
		v_list_ = new double[t_count_];

		for (int i = 0; i < t_count_; i++)
		{
			t_list_[i] = stod(tList_vec[i]);
		}
		for (int i = 0; i < t_count_; i++)
		{
			v_list_[i] = stod(vList_vec[i]);
		}
	}

	SetPortMap(_data_str, _port_map);
}

void PWLVoltageSource::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, true);
}

int PWLVoltageSource::GetReturnPrime()
{
	return kPrimeA + kPrimeE;
}

DeviceInfoStr PWLVoltageSource::GetDeviceInfo()
{
	return device_info_;
}

string PWLVoltageSource::GetInstanceName()
{
	return instance_name_;
}