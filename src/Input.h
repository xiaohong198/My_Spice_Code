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
#define byte my_byte
#include <windows.h>


using namespace std;

class Input
{

private:
	vector<string> SpecialClassNameVec;// 特殊类
	vector<InputDataStr*> SpecialClassVec;// 特殊类
	vector<InputDataStr> InputDataStrSVec;// 特殊类
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
	void MySplit(string str, string delimiter, vector<string>&tokens);


};

