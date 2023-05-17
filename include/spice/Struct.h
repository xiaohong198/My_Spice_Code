#pragma once
#include <iostream>
#include <vector>
#include <map>  

using namespace std;

struct DeviceInfoStr
{
	vector<int> xIndex;//未知量的位置
	int  additionalxCount;//额外变量的个数
};

struct ComparisonStr
{
	string ClassName;
	map<string, vector<string>> ParametersMap;
};

struct InputSCFStr
{
	string PSET;
	string DEVICE;
	map<string, string> ParametersMap;//参数名称及数值
};

struct InputCMDStr
{
	string Class;
	string Example;
	vector<string> Port;
	map<string, string> ParametersMap;//参数名称及数值
	bool IsPest;
};

// 位运算
enum ClassPrime
{
	PrimeA = 1,
	PrimeB = 2,
	PrimeP = 4,
	PrimeQ = 8,
	PrimeC = 16,
	PrimeE = 32
};
