#pragma once
#include "Struct.h"

#include <iostream>
#include <vector>
#include <map>  
#include <fstream>
#include <tinyxml.h>
#include <string>
#include <direct.h> 
#include <filesystem> 
#include <io.h>
#include <sstream>
#define byte my_byte
#include <windows.h>


using namespace std;

class Input
{

private:
	vector<string> SpecialClassNameVec;// 特殊类
	vector<InputDataStr*> SpecialClassVec;// 特殊类
	vector<InputDataStr> InputDataStrSVec;// 特殊类
	vector<InputSCFStr> InputSCFStrVec;
	vector<InputCMDStr> InputCMDStrVec;
	
	double max_electrode;


public:
	Input();
	~Input();
	void ReadSCF();
	void ReadCMD();
	void ReadXML();
	void ReadTXT();
	void ReadINI();
	void GetInput(vector<InputDataStr>& input_vec);

	// 字符串分割但是是通过大小写来改原来的
	std::vector<std::string> getSplitVec(string str, string str_trans, string delimiter);
	// 字符串分割
	std::vector<std::string> getSplitVec(string str, string delimiter);
	// 字符串大写
	string TransformUp(string _str);
	// 字符串小写
	string TransformLow(string _str);
	// 获取字符之间的内容
	string getContent(string _str, string begin_symbol, string end_symbol);
};

