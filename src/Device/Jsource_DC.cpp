#include "Jsource_DC.h"
REGISTER(Jsource_DC);
Jsource_DC::Jsource_DC() {
	//J_DC = 1;
}

Jsource_DC::~Jsource_DC() {
}

double Jsource_DC::eFunction(double t) {
	return J_DC;
}

double Jsource_DC::setIntegration(double* tList) {
	return J_DC * (tList[1] - tList[0]);
}

void Jsource_DC::getSubEIntegral(Eigen::VectorXd& subEIntegral, double* tList) {
	//�����͵�ѹ����Է���ο���
	//------v: +()- -----
	//------i: ������> -----
	subEIntegral(0) = -setIntegration(tList);
	subEIntegral(1) = setIntegration(tList);
}

//使用外部读取数据
void Jsource_DC::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;

	InstanceName = _DataStr.InstanceName;

	J_DC = stod(_DataStr.ParametersMap["J_DC"][0]);

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
void Jsource_DC::setDeviceInfo(map<string, int>& _PortMap)
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

int Jsource_DC::getReturnPrime()
{
	return PrimeE;
}

DeviceInfoStr Jsource_DC::getDeviceInfo()
{
	return DeviceInfo_;
}

string Jsource_DC::getInstanceName()
{
	return InstanceName;
}