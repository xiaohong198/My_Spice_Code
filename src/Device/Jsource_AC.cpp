#include "Jsource_AC.h"
REGISTER(Jsource_AC);
Jsource_AC::Jsource_AC() {
	//PeakAmplitude = 10;
	//Frequency = 50;
	//PhaseShift = 0;
}

Jsource_AC::~Jsource_AC() {
}

double Jsource_AC::eFunction(double t) {
	return PeakAmplitude * sin(2 * Frequency * PI * t + PhaseShift);
}

double Jsource_AC::setIntegration(double* tList) {
	return PeakAmplitude * (-cos(2 * Frequency * PI * tList[1] + PhaseShift) / (2 * Frequency * PI) + cos(2 * Frequency * PI * tList[0] + PhaseShift) / (2 * Frequency * PI));
}

void Jsource_AC::getSubEIntegral(Eigen::VectorXd& subEIntegral, double* tList) {
	subEIntegral(0) = -setIntegration(tList);
	subEIntegral(1) = setIntegration(tList);
}

//使用外部读取数据
void Jsource_AC::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;

	InstanceName = _DataStr.InstanceName;

	PeakAmplitude = stod(_DataStr.ParametersMap["PeakAmplitude"][0]);
	Frequency = stod(_DataStr.ParametersMap["Frequency"][0]);
	PhaseShift = stod(_DataStr.ParametersMap["PhaseShift"][0]);

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
void Jsource_AC::setDeviceInfo(map<string, int>& _PortMap)
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

int Jsource_AC::getReturnPrime()
{
	return PrimeE;
}

DeviceInfoStr Jsource_AC::getDeviceInfo()
{
	return DeviceInfo_;
}

string Jsource_AC::getInstanceName()
{
	return InstanceName;
}