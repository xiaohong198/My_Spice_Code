#include "Diode.h"
REGISTER(Diode);
Diode::Diode() {
	//Ron = 0.3;
	//Vf = 0.6;
	//Goff = 1e-8;
}

Diode::~Diode() {
}

double Diode::f(double Vd) {
	if (Vd > Vf)
		return (Vd - Vf) / Ron;
	else
		return (Vd - Vf) * Goff;
}

double Diode::G(double Vd) {
	if (Vd > Vf)
		return 1 / Ron;
	else
		return Goff;
}

void Diode::getSubPandPJacobian(const Eigen::VectorXd& nodeValue, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian) {
	double Vd = nodeValue(0) - nodeValue(1);
	subP.setZero();
	subP(0) = f(Vd);
	subP(1) = -f(Vd);
	subPJacobian.setZero();
	subPJacobian(0, 0) = G(Vd);
	subPJacobian(0, 1) = -G(Vd);
	subPJacobian(1, 0) = -G(Vd);
	subPJacobian(1, 1) = G(Vd);
}

//使用外部读取数据
void Diode::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;

	InstanceName = _DataStr.InstanceName;

	Ron = stod(_DataStr.ParametersMap["Ron"][0]);
	Vf = stod(_DataStr.ParametersMap["Vf"][0]);
	Goff = stod(_DataStr.ParametersMap["Goff"][0]);

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
void Diode::setDeviceInfo(map<string, int>& _PortMap)
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

int Diode::getReturnPrime()
{
	return PrimeP;
}

DeviceInfoStr Diode::getDeviceInfo()
{
	return DeviceInfo_;
}

string Diode::getInstanceName()
{
	return InstanceName;
}