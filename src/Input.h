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

	map<string, string> InitializeClassParametersMap;// xml���������ĸ�����ĳ�ʼ������
	map<string, string> InputClassParametersMap;// ����.scf��.cmd֮��Ҫ�������õ���Ĳ���

public:
	Input();
	~Input();
	void ReadSCF();
	void ReadCMD();
	void ReadCompareXML();
	void ReadTXT();
	
};

