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

struct InputStr
{
	string ClassName;//.cmd/.scf/.xml(Vsource_DC)
	string PsetName;//.cmd/.scf(IRFR3505/Vsource_DC_pset)
	string InstanceName;//.cmd(Mos1)
	vector<string> Port;//.cmd(n1 n3 n5 n4)
	map<string, vector<string>> ParametersMap;//参数名称及数值
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
