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
	vector<InputSCFStr> InputSCFStrVec;
	vector<InputCMDStr> InputCMDStrVec;
	vector<ComparisonStr> ComparisonStrVec;

	map<string, string> InitializeClassParametersMap;// xml解析出来的各个类的初始化参数
	map<string, string> InputClassParametersMap;// 读过.scf和.cmd之后要给器件用的类的参数

public:
	Input();
	~Input();
	void ReadSCF();
	void ReadCMD();
	void ReadCompareXML();
	void ReadTXT();
	
};

