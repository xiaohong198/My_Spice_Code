#include "JsourceDC.h"
REGISTER(JsourceDC);
JsourceDC::JsourceDC() {
}

JsourceDC::~JsourceDC() {
}

double JsourceDC::EFunction(double _t) {
	return j_dc_;
}

double JsourceDC::SetIntegration(double* _t_list) {
	return j_dc_ * (_t_list[1] - _t_list[0]);
}

void JsourceDC::GetSubEIntegral(Eigen::VectorXd& _sub_eIntegral, double* _t_list) {
	//�����͵�ѹ����Է���ο���
	//------v: +()- -----
	//------i: ������> -----
	_sub_eIntegral(0) = -SetIntegration(_t_list);
	_sub_eIntegral(1) = SetIntegration(_t_list);
}

//使用外部读取数据
void JsourceDC::SetInputData(InputStr _data_str, map<string, int>& _port_map)
{
	input_data_ = _data_str;

	instance_name_ = _data_str.instance_name;

	j_dc_ = stod(_data_str.parameters_map["J_DC"][0]);

	SetPortMap(_data_str, _port_map);
}

//对器件应用端口号
void JsourceDC::SetDeviceInfo(map<string, int>& _port_map)
{
	device_info_ = SetDeviceInfoType(_port_map, false);
}

int JsourceDC::GetReturnPrime()
{
	return kPrimeE;
}

DeviceInfoStr JsourceDC::GetDeviceInfo()
{
	return device_info_;
}

string JsourceDC::GetInstanceName()
{
	return instance_name_;
}