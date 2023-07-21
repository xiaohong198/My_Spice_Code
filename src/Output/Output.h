#pragma once
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <direct.h>
#include <filesystem>
#include <io.h>
#include <typeinfo>
#include <variant>
#include <string>

using namespace std;
using var_t = std::variant<std::string, int, double, Eigen::VectorXd>;

class Output
{
public:
	Output();
	~Output();
	void SaveTxt(string, std::vector<var_t>, int _size = 1);
};
