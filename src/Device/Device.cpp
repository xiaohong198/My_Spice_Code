#include "Device.h"

Device::Device() {
}

Device::~Device() {
}

void Device::GetSubA(Eigen::MatrixXd& _sub_a) {
}

void Device::GetSubB(Eigen::MatrixXd& _sub_b) {
}

void Device::GetSubEIntegral(Eigen::VectorXd& _sub_e, double* _t_list) {
}

void Device::GetSubPandPJacobian(const Eigen::VectorXd& _node_value, Eigen::VectorXd& _sub_p, Eigen::MatrixXd& _sub_p_jacobian) {
}

void Device::GetSubQandQJacobian(const Eigen::VectorXd& _node_value, Eigen::VectorXd& _sub_q, Eigen::MatrixXd& _sub_q_jacobian) {
}

void Device::GetSubC(const Eigen::VectorXd& _node_value, Eigen::MatrixXd& _sub_c) {
}

int Device::GetReturnPrime()
{
	return 0;
}

void Device::SetDeviceInfo(map<string, int>& _port_map)
{
}

void Device::SetInputData(InputStr _data_str, map<string, int>& _port_data)
{
}

DeviceInfoStr Device::GetDeviceInfo()
{
	DeviceInfoStr str_null;
	return str_null;
}

string Device::GetInstanceName()
{
	return instance_name_;
}

void Device::SetPortMap(InputStr _data_str, map<string, int>& _port_map)
{
	//端口号
	int max_port = 0;
	//获得最大端口号编号
	for (auto iter_map = _port_map.begin(); iter_map != _port_map.end(); iter_map++)
	{
		max_port < iter_map->second ? max_port = iter_map->second : max_port;
	}
	for (auto index_port = 0; index_port < _data_str.port.size(); index_port++)
	{
		//如果端口号直接是数字
		if (std::regex_match(_data_str.port[index_port], std::regex("-?\\d+(\\.\\d*)?")))
		{
			max_port < stoi(_data_str.port[index_port]) ? max_port = stoi(_data_str.port[index_port]) : max_port;
			_port_map.insert({ _data_str.port[index_port] , stoi(_data_str.port[index_port]) });
			// 未完成
		}
		//如果端口号是用标识符代表
		else
		{
			if (_port_map.find(_data_str.port[index_port]) != _port_map.end())
			{
				continue;
			}
			else
			{
				_port_map.insert({ _data_str.port[index_port] , ++max_port });
			}
		}
	}
	_port_map.insert({ "- MaxPortIndex -",max_port });
	_port_map["- MaxPortIndex -"] = max_port;
}

DeviceInfoStr Device::SetDeviceInfoType(map<string, int>& _port_map, bool _type)
{
	DeviceInfoStr device_info;
	//端口号应用
	int _max_port_index = _port_map["- MaxPortIndex -"];

	for (auto index_port = 0; index_port < input_data_.port.size(); index_port++)
	{
		string port_name = input_data_.port[index_port];
		if (std::find(voltage_x_index_.begin(), voltage_x_index_.end(), _port_map[port_name]) == voltage_x_index_.end())
		{
			voltage_x_index_.push_back(_port_map[port_name]);
		}
		device_info.x_index.push_back(_port_map[port_name]);
	}
	if (_type)
	{
		device_info.x_index.push_back(++_max_port_index);
		current_x_index_.push_back(_max_port_index);
		device_info.additional_index.push_back(_max_port_index);
	}
	_port_map["- MaxPortIndex -"] = _max_port_index;
	return device_info;
}