#include "Diode.h"
REGISTER(Diode);
Diode::Diode() {
}

Diode::~Diode() {
}

double Diode::F(double _Vd) {
	if (_Vd > vf_)
		return (_Vd - vf_) / ron_;
	else
		return (_Vd - vf_) * goff_;
}

double Diode::G(double _Vd) {
	if (_Vd > vf_)
		return 1 / ron_;
	else
		return goff_;
}

void Diode::GetSubPandPJacobian(const Eigen::VectorXd& _node_value, Eigen::VectorXd& _sub_p, Eigen::MatrixXd& _sub_p_jacobian) {
	double Vd = _node_value(0) - _node_value(1);
	_sub_p.setZero();
	_sub_p(0) = F(Vd);
	_sub_p(1) = -F(Vd);
	_sub_p_jacobian.setZero();
	_sub_p_jacobian(0, 0) = G(Vd);
	_sub_p_jacobian(0, 1) = -G(Vd);
	_sub_p_jacobian(1, 0) = -G(Vd);
	_sub_p_jacobian(1, 1) = G(Vd);
}

//使用外部读取数据
void Diode::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;

	instance_name_ = _data_str.instance_name;

	ron_ = stod(_data_str.parameters_map["Ron"][0]);
	vf_ = stod(_data_str.parameters_map["Vf"][0]);
	goff_ = stod(_data_str.parameters_map["Goff"][0]);

	SetPortMap(_data_str, _port_map);
}

//对器件应用端口号
void Diode::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, false);
}

int Diode::GetReturnPrime()
{
	return kPrimeP;
}

DeviceInfoStr Diode::GetDeviceInfo()
{
	return device_info_;
}

string Diode::GetInstanceName()
{
	return instance_name_;
}