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
	SpiceString* spice_string_;

public:
	map<string, InputStr> xml_compare_;// key 类名（SpiceMosfet） value 类数据结构体
	map<string, InputStr> scf_compare_;// key PSET名（3505） value 类数据结构体
	map<string, InputStr> cmd_compare_;// key 实例名（Mos1） value 类数据结构体
	map<string, InputStr> user_compare_;// 交给器件类的key 器件名称（3505） value 类数据结构体
	map<string, int> port_compare_;// key 端口号（n0） value 端口号编号
	map<string, int> hint_compare_;// key 端口号（n0） value 端口号初始值
	map<string, PlotStr> plot_compare_;// key 文件名（n0） value 文件内容方式
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
	map<string, PlotStr> GetPlotCompare();
};
