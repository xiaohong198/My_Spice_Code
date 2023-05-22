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
	vector<ComparisonStr> DefaultParameterStrVec;
	vector<ComparisonStr> UserParameterStrVec;// 交给器件类的

public:
	Input();
	~Input();
	void ReadSCF();
	void ReadCMD();
	void ReadCompareXML();
	void SetParameter();
};

