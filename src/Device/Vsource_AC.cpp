#include "Vsource_AC.h"
REGISTER(Vsource_AC);
Vsource_AC::Vsource_AC() {
	//PeakAmplitude = 10;
	//Frequency = 50;
	//PhaseShift = 0;
}
Vsource_AC::~Vsource_AC() {
}

double Vsource_AC::eFunction(double t) {
	return PeakAmplitude * sin(2 * Frequency * PI * t + PhaseShift);
	//    return 100 * t;
}

double Vsource_AC::setIntegration(double* tList) {
	return PeakAmplitude * (-cos(2 * Frequency * PI * tList[1] + PhaseShift) / (2 * Frequency * PI) + cos(2 * Frequency * PI * tList[0] + PhaseShift) / (2 * Frequency * PI));
	//    return 50 * (pow(t2, 2) - pow(t1, 2));
}

void Vsource_AC::getSubA(Eigen::MatrixXd& subA) {
	subA.setZero();
	subA(0, 2) = 1;
	subA(1, 2) = -1;
	subA(2, 0) = 1;
	subA(2, 1) = -1;
}

void Vsource_AC::getSubEIntegral(Eigen::VectorXd& subEIntegral, double* tList) {
	subEIntegral.setZero();
	subEIntegral(2) = setIntegration(tList);
}

void Vsource_AC::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;
	InstanceName = _DataStr.InstanceName;

	PeakAmplitude = stod(_DataStr.ParametersMap["PeakAmplitude"][0]);
	Frequency = stod(_DataStr.ParametersMap["Frequency"][0]);
	PhaseShift = stod(_DataStr.ParametersMap["PhaseShift"][0]);

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

void Vsource_AC::setDeviceInfo(map<string, int>& _PortMap)
{
	//DeviceInfo_.xIndex.push_back(1);
	//DeviceInfo_.xIndex.push_back(0);
	//DeviceInfo_.xIndex.push_back(9);
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

int Vsource_AC::getReturnPrime()
{
	return PrimeA + PrimeE;
}

DeviceInfoStr Vsource_AC::getDeviceInfo()
{
	return DeviceInfo_;
}

string Vsource_AC::getInstanceName()
{
	return InstanceName;
}