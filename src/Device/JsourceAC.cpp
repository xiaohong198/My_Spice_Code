#include "JsourceAC.h"
REGISTER(JsourceAC);
JsourceAC::JsourceAC() {
}

JsourceAC::~JsourceAC() {
}

double JsourceAC::EFunction(double _t) {
	return peak_amplitude_ * sin(2 * frequency_ * kPI * _t + phase_shift_);
}

double JsourceAC::SetIntegration(double* _t_list) {
	return peak_amplitude_ * (-cos(2 * frequency_ * kPI * _t_list[1] + phase_shift_) / (2 * frequency_ * kPI) + cos(2 * frequency_ * kPI * _t_list[0] + phase_shift_) / (2 * frequency_ * kPI));
}

void JsourceAC::GetSubEIntegral(Eigen::VectorXd& _sub_eIntegral, double* _t_list) {
	_sub_eIntegral(0) = -SetIntegration(_t_list);
	_sub_eIntegral(1) = SetIntegration(_t_list);
}

//使用外部读取数据
void JsourceAC::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;

	instance_name_ = _data_str.instance_name;

	peak_amplitude_ = stod(_data_str.parameters_map["PeakAmplitude"][0]);
	frequency_ = stod(_data_str.parameters_map["Frequency"][0]);
	phase_shift_ = stod(_data_str.parameters_map["PhaseShift"][0]);

	SetPortMap(_data_str, _port_map);
}

//对器件应用端口号
void JsourceAC::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, false);
}

int JsourceAC::GetReturnPrime()
{
	return kPrimeE;
}

DeviceInfoStr JsourceAC::GetDeviceInfo()
{
	return device_info_;
}

string JsourceAC::GetInstanceName()
{
	return instance_name_;
}