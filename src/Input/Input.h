#pragma once
#include "Struct.h"
#include "SpiceString.h"
#include <fstream>
#include <tinyxml.h>
#include <direct.h> 
#include <io.h>
#include <sstream>
#define byte my_byte
#include <windows.h>
using namespace std;

class Input
{
private:
	SpiceString * SpiceString_;

public:
	map<string, InputStr> XMLParameterStrMap;// key 类名（SpiceMosfet） value 类数据结构体
	map<string, InputStr> SCFParameterStrMap;// key PSET名（3505） value 类数据结构体
	map<string, InputStr> CMDParameterStrMap;// key 实例名（Mos1） value 类数据结构体
	map<string, InputStr> UserParameterStrMap;// 交给器件类的key 器件名称（3505） value 类数据结构体
	map<string, int> PortCompareMap;
	map<string, int> HintCompareMap;
public:
	Input();
	~Input();
	void ReadSCF();
	void ReadCMD();
	void ReadCompareXML();
	void SetParameter();
	map<string, InputStr> GetParameter();
	map<string, int> GetPortCompare();
	map<string, int> GetHintCompare();
};

