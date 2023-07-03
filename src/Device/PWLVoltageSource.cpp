#include "PWLVoltageSource.h"

REGISTER(PWLVoltageSource);
PWLVoltageSource::PWLVoltageSource() {
}
PWLVoltageSource::~PWLVoltageSource() {
	delete[] tList;
	delete[] vList;
}

double PWLVoltageSource::eFunction(double t) {
	if (t < tList[0]) {
		return vList[0];
	}
	else if (t >= tList[tCount - 1]) {
		return vList[tCount - 1];
	}
	else {
		for (int i = 1; i < tCount; i++) {
			if (t < tList[i]) {
				return ((vList[i] - vList[i - 1]) / (tList[i] - tList[i - 1]) * (t - tList[i - 1]) + vList[i - 1]);
				break;
			}
		}
	}
	return 0;
}

double PWLVoltageSource::setIntegration(double* tList) {
	double t1 = tList[0];
	double t2 = tList[1];
	double PSLIntegral = 0;
	double vt1 = eFunction(t1);
	double vt2 = eFunction(t2);
	//默认t1<t2;
	int Locationt1 = tCount;
	int Locationt2 = tCount;
	for (int i = 0; i < tCount; i++) {//定位t1
		if (t1 < tList[i]) {
			Locationt1 = i;
			break;
		}
	}
	for (int i = 0; i < tCount; i++) {//定位t2
		if (t2 < tList[i]) {
			Locationt2 = i;
			break;
		}
	}
	if (Locationt1 == Locationt2) {
		PSLIntegral = (vt1 + vt2) * (t2 - t1) / 2;
	}
	else {
		PSLIntegral += (vt1 + vList[Locationt1]) * (tList[Locationt1] - t1) * 0.5;
		PSLIntegral += (vt2 + vList[Locationt2 - 1]) * (t2 - tList[Locationt2 - 1]) * 0.5;
		for (int i = Locationt1; i < Locationt2 - 1; i++) {//如果t1和t2在相邻区间，这个循环不会运行
			PSLIntegral += (vList[i] + vList[i + 1]) * (tList[i + 1] - tList[i]) * 0.5;
		}
	}
	return PSLIntegral;
}

void PWLVoltageSource::getSubA(Eigen::MatrixXd& subA) {
	subA.setZero();
	subA(0, 2) = 1;
	subA(1, 2) = -1;
	subA(2, 0) = 1;
	subA(2, 1) = -1;
}

void PWLVoltageSource::getSubEIntegral(Eigen::VectorXd& subEIntegral, double* tList) {
	subEIntegral.setZero();
	subEIntegral(2) = (eFunction(tList[0]) + eFunction(tList[1])) / 2 * (tList[1] - tList[0]);
}

void PWLVoltageSource::setInputData(InputStr _DataStr, map<string, int>& _PortMap)
{
	InputData = _DataStr;
	InstanceName = _DataStr.InstanceName;
	if (_DataStr.ParametersMap.find("pwl") != _DataStr.ParametersMap.end())
	{
		vector<string> pwl_vec = _DataStr.ParametersMap["pwl"];
		tCount = pwl_vec.size() / 2;
		tList = new double[tCount];
		vList = new double[tCount];

		for (int i = 0; i < tCount; i++)
		{
			tList[i] = stod(pwl_vec[i * 2]);
			vList[i] = stod(pwl_vec[(i * 2) + 1]);
		}
	}
	else
	{
		tCount = stod(_DataStr.ParametersMap["tCount"][0]);
		vector<string> tList_vec = _DataStr.ParametersMap["tList"];
		vector<string> vList_vec = _DataStr.ParametersMap["vList"];
		tList = new double[tCount];
		vList = new double[tCount];

		for (int i = 0; i < tCount; i++)
		{
			tList[i] = stod(tList_vec[i]);
		}
		for (int i = 0; i < tCount; i++)
		{
			vList[i] = stod(vList_vec[i]);
		}
	}

	//�˿ں�
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
			// δ���
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

void PWLVoltageSource::setDeviceInfo(map<string, int>& _PortMap)
{
	//DeviceInfo_.xIndex.push_back(8);
	//DeviceInfo_.xIndex.push_back(5);
	//DeviceInfo_.xIndex.push_back(10);
	//return;
	//�˿ں�Ӧ��
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

int PWLVoltageSource::getReturnPrime()
{
	return PrimeA + PrimeE;
}

DeviceInfoStr PWLVoltageSource::getDeviceInfo()
{
	return DeviceInfo_;
}

string PWLVoltageSource::getInstanceName()
{
	return InstanceName;
}