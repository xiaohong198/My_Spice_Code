#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct DeviceInfoStr
{
	vector<int> x_index;//未知量的位置
	vector<int> additional_index;//额外变量
};

struct InputStr
{
	string class_name;//.cmd/.scf/.xml(Vsource_DC)
	string pset_name;//.cmd/.scf(IRFR3505/Vsource_DC_pset)
	string instance_name;//.cmd(Mos1)
	vector<string> port;//.cmd(n1 n3 n5 n4)
	map<string, vector<string>> parameters_map;//参数名称及数值
};

struct PlotVIStr
{
	int plot_type;//time:0 v:1 i:2
	vector<string> plot_value_vec;//PWLVs n2
};

struct PlotStr
{
	string plot_name;//Mos1_paper_debug2.txt
	vector<PlotVIStr> plot_vi_vec;//time() v(n1) i(PWLVs n2)
};

// 位运算
enum ClassPrime
{
	kPrimeA = 1,
	kPrimeB = 2,
	kPrimeP = 4,
	kPrimeQ = 8,
	kPrimeC = 16,
	kPrimeE = 32
};
