#include <iostream>
#include "Resistor.h"
REGISTER(Resistor);
using namespace std;

Resistor::Resistor() {
}

void Resistor::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;

	InstanceName = _DataStr.InstanceName;

	resistance = stod(_DataStr.ParametersMap["resistance"][0]);

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
				switch (index_port)
				{
				case 0:
					_PortMap.insert({ _DataStr.Port[0] , ++max_port });
					break;
				case 1:
					_PortMap.insert({ _DataStr.Port[1] , ++max_port });
					break;
				default:
					break;
				}
			}
		}
	}
	_PortMap.insert({ "- MaxPortIndex -",max_port });
	_PortMap["- MaxPortIndex -"] = max_port;
}

void Resistor::setDeviceInfo(map<string, int>& _PortMap)
{
	//端口号应用
	for (auto index_port = 0; index_port < InputData.Port.size(); index_port++)
	{
		string port_name = InputData.Port[index_port];
		DeviceInfo_.xIndex.push_back(_PortMap[port_name]);
	}
}

void Resistor::getSubA(Eigen::MatrixXd& subA) {
    subA(0, 0) = 1 / resistance;
    subA(0, 1) = -1 / resistance;
    subA(1, 0) = -1 / resistance;
    subA(1, 1) = 1 / resistance;
}

int Resistor::getReturnPrime()
{
	return PrimeA;
}

DeviceInfoStr Resistor::getDeviceInfo()
{
	return DeviceInfo_;
}

Resistor::~Resistor() {

}

string Resistor::getInstanceName()
{
	return InstanceName;
}