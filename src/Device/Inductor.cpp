#include "Inductor.h"
REGISTER(Inductor);
Inductor::Inductor() {
}
Inductor::~Inductor() {
}

void Inductor::GetSubA(Eigen::MatrixXd& _sub_a) {
	_sub_a(0, 2) = 1;
	_sub_a(1, 2) = -1;
	_sub_a(2, 0) = -1;
	_sub_a(2, 1) = 1;
}

void Inductor::GetSubB(Eigen::MatrixXd& _sub_b) {
	_sub_b.setZero();
	_sub_b(2, 2) = inductance_;
}

void Inductor::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;
	//器件实例名称
	instance_name_ = _data_str.instance_name;
	//参数
	inductance_ = stod(_data_str.parameters_map["Inductance"][0]);

	SetPortMap(_data_str, _port_map);
}

void Inductor::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, true);
}

int Inductor::GetReturnPrime()
{
	return kPrimeA + kPrimeB;
}

DeviceInfoStr Inductor::GetDeviceInfo()
{
	return device_info_;
}

string Inductor::GetInstanceName()
{
	return instance_name_;
}