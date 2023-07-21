#include "VsourceDC.h"
REGISTER(VsourceDC);

VsourceDC::VsourceDC() {
}

VsourceDC::~VsourceDC() {
}

double VsourceDC::EFunction(double _t) {
	return V_DC_;
}

double VsourceDC::SetIntegration(double* _t_list) {
	return V_DC_ * (_t_list[1] - _t_list[0]);
}

void VsourceDC::GetSubA(Eigen::MatrixXd& _sub_a) {
	_sub_a.setZero();
	_sub_a(0, 2) = 1;
	_sub_a(1, 2) = -1;
	_sub_a(2, 0) = 1;
	_sub_a(2, 1) = -1;
}

void VsourceDC::GetSubEIntegral(Eigen::VectorXd& _sub_e_integral, double* _t_list) {
	_sub_e_integral.setZero();
	_sub_e_integral(2) = SetIntegration(_t_list);
}

void VsourceDC::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;
	instance_name_ = _data_str.instance_name;

	V_DC_ = stod(_data_str.parameters_map["V_DC"][0]);

	SetPortMap(_data_str, _port_map);
}

void VsourceDC::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, true);
}

int VsourceDC::GetReturnPrime()
{
	return kPrimeA + kPrimeE;
}

DeviceInfoStr VsourceDC::GetDeviceInfo()
{
	return device_info_;
}

string VsourceDC::GetInstanceName()
{
	return instance_name_;
}