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
	vector<string> SpecialClassNameVec;// ������
	vector<InputDataStr*> SpecialClassVec;// ������
	vector<InputDataStr> InputDataStrSVec;// ������
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

	// �ַ����ָ����ͨ����Сд����ԭ����
	std::vector<std::string> getSplitVec(string str, string str_trans, string delimiter);
	// �ַ����ָ�
	std::vector<std::string> getSplitVec(string str, string delimiter);
	// �ַ�����д
	string TransformUp(string _str);
	// �ַ���Сд
	string TransformLow(string _str);
	// ��ȡ�ַ�֮�������
	string getContent(string _str, string begin_symbol, string end_symbol);
};

