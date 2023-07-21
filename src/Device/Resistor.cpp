#include "Resistor.h"
REGISTER(Resistor);
Resistor::Resistor() {
}

Resistor::~Resistor() {
}

void Resistor::GetSubA(Eigen::MatrixXd& _subA) {
	_subA(0, 0) = 1 / resistance_;
	_subA(0, 1) = -1 / resistance_;
	_subA(1, 0) = -1 / resistance_;
	_subA(1, 1) = 1 / resistance_;
}

void Resistor::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;

	instance_name_ = _data_str.instance_name;

	resistance_ = stod(_data_str.parameters_map["resistance"][0]);

	SetPortMap(_data_str, _port_map);
}

void Resistor::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, false);
}

int Resistor::GetReturnPrime()
{
	return kPrimeA;
}

DeviceInfoStr Resistor::GetDeviceInfo()
{
	return device_info_;
}

string Resistor::GetInstanceName()
{
	return instance_name_;
}