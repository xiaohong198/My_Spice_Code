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
	std::vector<std::string> getSplitVec(string str, string delimiter, string str_trans = "", bool is_remove = false);
	//// �ַ����ָ�
	//std::vector<std::string> getSplitVec(string str, string delimiter, bool is_remove = false);
	// �ַ�����д
	string TransformUp(string _str);
	// �ַ���Сд
	string TransformLow(string _str);
	// ��ȡ�ַ�֮�������
	string getContent(string _str, string begin_symbol, string end_symbol);
	// ɾ���ַ������ַ�
	string RemoveChars(string _str, string _chars);

};

