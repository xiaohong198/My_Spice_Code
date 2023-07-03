#include "Capacitor.h"
REGISTER(Capacitor);
Capacitor::Capacitor() {
	//capacitance = 1;
}

Capacitor::~Capacitor() {
}

void Capacitor::getSubB(Eigen::MatrixXd& subB) {
	//subA.setZero();
	subB(0, 0) = capacitance;
	subB(0, 1) = -capacitance;
	subB(1, 0) = -capacitance;
	subB(1, 1) = capacitance;
}

//使用外部读取数据
void Capacitor::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;

	InstanceName = _DataStr.InstanceName;

	capacitance = stod(_DataStr.ParametersMap["capacitance"][0]);

	//端口号
	int max_port = 0;
	//获得最大端口号编号
	for (auto iter_map = _PortMap.begin(); iter_map != _PortMap.end(); iter_map++)
	{
		max_port < iter_map->second ? max_port = iter_map->second : max_port;
	}
	for (auto index_port = 0; index_port < _DataStr.Port.size(); index_port++)
	{
		//如果端口号直接是数字
		if (std::regex_match(_DataStr.Port[index_port], std::regex("-?\\d+(\\.\\d*)?")))
		{
			max_port < stoi(_DataStr.Port[index_port]) ? max_port = stoi(_DataStr.Port[index_port]) : max_port;
			_PortMap.insert({ _DataStr.Port[index_port] , stoi(_DataStr.Port[index_port]) });
			// 未完成
		}
		//如果端口号是用标识符代表
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

//对器件应用端口号
void Capacitor::setDeviceInfo(map<string, int>& _PortMap)
{
	//端口号应用
	for (auto index_port = 0; index_port < InputData.Port.size(); index_port++)
	{
		string port_name = InputData.Port[index_port];
		DeviceInfo_.xIndex.push_back(_PortMap[port_name]);
		if (std::find(VoltageXIndex.begin(), VoltageXIndex.end(), _PortMap[port_name]) == VoltageXIndex.end())
		{
			VoltageXIndex.push_back(_PortMap[port_name]);
		}
	}
}

int Capacitor::getReturnPrime()
{
	return PrimeB;
}

DeviceInfoStr Capacitor::getDeviceInfo()
{
	return DeviceInfo_;
}

string Capacitor::getInstanceName()
{
	return InstanceName;
}