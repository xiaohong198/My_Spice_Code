#include "VsourceAC.h"
REGISTER(VsourceAC);
VsourceAC::VsourceAC() {
}
VsourceAC::~VsourceAC() {
}

double VsourceAC::EFunction(double _t) {
	return peak_amplitude_ * sin(2 * frequency_ * kPI * _t + phase_shift_);
	//    return 100 * t;
}

double VsourceAC::SetIntegration(double* _t_list) {
	return peak_amplitude_ * (-cos(2 * frequency_ * kPI * _t_list[1] + phase_shift_) / (2 * frequency_ * kPI) + cos(2 * frequency_ * kPI * _t_list[0] + phase_shift_) / (2 * frequency_ * kPI));
	//    return 50 * (pow(t2, 2) - pow(t1, 2));
}

void VsourceAC::GetSubA(Eigen::MatrixXd& _sub_a) {
	_sub_a.setZero();
	_sub_a(0, 2) = 1;
	_sub_a(1, 2) = -1;
	_sub_a(2, 0) = 1;
	_sub_a(2, 1) = -1;
}

void VsourceAC::GetSubEIntegral(Eigen::VectorXd& _sub_eIntegral, double* _t_list) {
	_sub_eIntegral.setZero();
	_sub_eIntegral(2) = SetIntegration(_t_list);
}

void VsourceAC::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;
	instance_name_ = _data_str.instance_name;

	peak_amplitude_ = stod(_data_str.parameters_map["PeakAmplitude"][0]);
	frequency_ = stod(_data_str.parameters_map["Frequency"][0]);
	phase_shift_ = stod(_data_str.parameters_map["PhaseShift"][0]);

	SetPortMap(_data_str, _port_map);
}

void VsourceAC::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, true);
}

int VsourceAC::GetReturnPrime()
{
	return kPrimeA + kPrimeE;
}

DeviceInfoStr VsourceAC::GetDeviceInfo()
{
	return device_info_;
}

string VsourceAC::GetInstanceName()
{
	return instance_name_;
}