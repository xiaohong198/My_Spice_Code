#pragma once
#include <iostream>
#include <vector>
#include <map>  

using namespace std;

struct DeviceInfoStr
{
	//char deviceType;
	//int  deviceIndexPerClass;
	vector<int> xIndex;//未知量的位置
	int  additionalxCount;//额外变量的个数
};

//输入xml参数结构体
struct InputDataStr
{
	string InstanceName;//自定义名称
	string  PSET;//类名
	vector<double>  EelectrodesVec;//electrode数值
	map<string,double> ParametersMap;//参数名称及数值
	bool IsSpecial;//是否是特殊类
	double MaxElectrode;//特殊类的最大数值
};
