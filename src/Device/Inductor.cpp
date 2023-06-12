#include "Inductor.h"

REGISTER(Inductor);
Inductor::Inductor() {
}

void Inductor::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;
	//器件实例名称
	InstanceName = _DataStr.InstanceName;
	//参数
	Inductance = stod(_DataStr.ParametersMap["Inductance"][0]);
	//端口号
	int max_port = 0;
	for (auto iter_map = _PortMap.begin(); iter_map != _PortMap.end(); iter_map++)
	{
		max_port < iter_map->second ? max_port = iter_map->second : max_port;
	}
	for (auto index_port = 0; index_port < _DataStr.Port.size(); index_port++)
	{
		if (std::regex_match(_DataStr.Port[index_port], std::regex("-?\\d+(\\.\\d*)?")))
		{
			max_port < stoi(_DataStr.Port[index_port]) ? max_port = stoi(_DataStr.Port[index_port]) : max_port;
			_PortMap.insert({ _DataStr.Port[index_port] , stoi(_DataStr.Port[index_port]) });
			// 未完成
		}
		else
		{
			if (_PortMap.find(_DataStr.Port[index_port]) != _PortMap.end())
			{
				continue;
			}
			else
			{
				_PortMap.insert({ _DataStr.Port[index_port] , ++max_port });
				//VoltageXIndex.push_back(max_port);
			}
		}
	}
	_PortMap.insert({ "- MaxPortIndex -",max_port });
	_PortMap["- MaxPortIndex -"] = max_port;
}

void Inductor::setDeviceInfo(map<string, int>& _PortMap)
{
	//DeviceInfo_.xIndex.push_back(5);
	//DeviceInfo_.xIndex.push_back(7);
	//DeviceInfo_.xIndex.push_back(11);
	//return;
	//端口号应用
	int _max_port_index = _PortMap["- MaxPortIndex -"];
	for (auto index_port = 0; index_port < InputData.Port.size(); index_port++)
	{
		string port_name = InputData.Port[index_port];
		DeviceInfo_.xIndex.push_back(_PortMap[port_name]);
		if (std::find(VoltageXIndex.begin(), VoltageXIndex.end(), _PortMap[port_name]) == VoltageXIndex.end())
		{
			VoltageXIndex.push_back(_PortMap[port_name]);
		}
	}
	DeviceInfo_.xIndex.push_back(++_max_port_index);
	_PortMap["- MaxPortIndex -"] = _max_port_index;
	CurrentXIndex.push_back(_max_port_index);
}

Inductor::~Inductor() {
}

void Inductor::getSubA(Eigen::MatrixXd& subA) {
	subA(0, 2) = 1;
	subA(1, 2) = -1;
	subA(2, 0) = -1;
	subA(2, 1) = 1;
}

void Inductor::getSubB(Eigen::MatrixXd& subB) {
	subB.setZero();
	subB(2, 2) = Inductance;
}

int Inductor::getReturnPrime()
{
	return PrimeA + PrimeB;
}

DeviceInfoStr Inductor::getDeviceInfo()
{
	return DeviceInfo_;
}

string Inductor::getInstanceName()
{
	return InstanceName;
}