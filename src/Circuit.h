#pragma once
#include <fstream>
#include <vector>
#include "Device.h"
#include "structDeviceInfo.h"
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Vsource_DC.h"
#include "Vsource_AC.h"
#include "Jsource_DC.h"
#include "Jsource_AC.h"
#include "PWLVoltageSource.h"
#include "Diode.h"
#include "MOA.h"
#include "TabulatedIVCurveDevice.h"
#include "SurgeArrester.h"
#include "SpiceMosfet.h"
#include "SpiceMosLevel1Test.h"
#include "SpiceDiode.h" 
#include <iostream>
#include <vector>
#include <map>  
#include "Struct.h"

#include <tinyxml.h>
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>


using namespace std;

//struct DeviceInfoStr
//{
//	char deviceType;
//	int  deviceIndexPerClass;
//	int  xCount;//未知量的个数
//	vector<int> xIndex;//未知量的位置
//	int  additionalxCount;//额外变量的个数
//};
//
////输入xml参数结构体
//struct InputDataStr
//{
//	string InstanceName;//自定义名称
//	string  PSET;//类名
//	vector<double>  EelectrodesVec;//electrode数值
//	map<string,double> ParametersMap;//参数名称及数值
//	bool IsSpecial;//是否是特殊类
//	double MaxElectrode;//特殊类的最大数值
//};


class Device;
class structDeviceInfo;
class Circuit
{
	friend class Solver;
	friend class Solver_EulerBackward;
	friend class Solver_TR;
protected:
	//int timeInvariantDeviceCount;
	int timeVariantDeviceCount;
	int excitationDeviceCount;
	int DeviceCount;
	int nodeCount;
	int AdditaionalxCount;//未知量x中有多少个除节点电压以外的变量
	int matrixDimension;

	//vector <Device*> vecTimeInvariantDevice;
	vector <Device*> vecTimeVariantDevice;
	vector <Device*> vecExcitationDevice;//是直流源、交流源这种激励源E(t)单独一类，受控源依然放在前两类中
	vector <Device*> vecDevice;

	//vector <structDeviceInfo*> vecDeviceInfo;
	vector <DeviceInfoStr> vecTimeInvariantDeviceInfo;
	vector <DeviceInfoStr> vecTimeVariantDeviceInfo;
	vector <DeviceInfoStr> vecExcitationDeviceInfo;
	vector <DeviceInfoStr> vecDeviceInfo;


	vector<string> SpecialClassNameVec;// 特殊类
	vector<InputDataStr*> SpecialClassVec;// 特殊类
	vector<InputDataStr> InputDataStrSVec;// 特殊类
	

	double max_electrode;


public:
	Circuit();
	~Circuit();
	//得到vector <Device*> f和deviceCount
#if 0
	void Read_Inputfile();

#endif // 0
	void Read_InputXML();
	void Read_InputTXT();
	void MySplit(string str, string delimiter, vector<string>&tokens);

};

