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

