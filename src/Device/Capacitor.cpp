#include "Capacitor.h"
REGISTER(Capacitor);
Capacitor::Capacitor() {
}

Capacitor::~Capacitor() {
}

void Capacitor::GetSubB(Eigen::MatrixXd& _sub_b) {
	//subA.setZero();
	_sub_b(0, 0) = capacitance_;
	_sub_b(0, 1) = -capacitance_;
	_sub_b(1, 0) = -capacitance_;
	_sub_b(1, 1) = capacitance_;
}

//使用外部读取数据
void Capacitor::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;

	instance_name_ = _data_str.instance_name;

	capacitance_ = stod(_data_str.parameters_map["capacitance"][0]);

	SetPortMap(_data_str, _port_map);
}

//对器件应用端口号
void Capacitor::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, false);
}

int Capacitor::GetReturnPrime()
{
	return kPrimeB;
}

DeviceInfoStr Capacitor::GetDeviceInfo()
{
	return device_info_;
}

string Capacitor::GetInstanceName()
{
	return instance_name_;
}