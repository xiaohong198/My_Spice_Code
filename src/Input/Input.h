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
	map<string, InputStr> XMLParameterStrMap;// key ������SpiceMosfet�� value �����ݽṹ��
	map<string, InputStr> SCFParameterStrMap;// key PSET����3505�� value �����ݽṹ��
	map<string, InputStr> CMDParameterStrMap;// key ʵ������Mos1�� value �����ݽṹ��
	map<string, InputStr> UserParameterStrMap;// �����������key �������ƣ�3505�� value �����ݽṹ��
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

