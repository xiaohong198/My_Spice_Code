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
	// 字符串分割但是是通过大小写来改原来的(str 字符串 delimiter 分割字符 str_trans 大小写转换后的 is_remove 是否保留空格)
	std::vector<std::string> GetSplitVec(string, string, string str_trans = "", bool is_remove = false);
	// 字符串大写
	string TransformUp(string);
	// 字符串小写
	string TransformLow(string);
	// 获取字符之间的内容
	string GetContent(string, string, string);
	// 删除字符串中字符
	string RemoveChars(string, string);
};
