#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <filesystem> 


using namespace std;

class SpiceString
{
public:
	SpiceString();
	~SpiceString();
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

