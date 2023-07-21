#pragma once
#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <direct.h>
#include <filesystem>
#include <io.h>
#include <typeinfo>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "Input/Circuit.h"
#include "Input/Configuration.h"
#include "Newton/Newton.h"
#include "Output/Output.h"
#include "Eigen/src/Core/Matrix.h"
using namespace std;
class Newton;
class Solver
{
protected:

	Eigen::MatrixXd A_;
	Eigen::MatrixXd B_;

	Eigen::MatrixXd P_Jacobian_;//时变电容电感
	Eigen::MatrixXd Q_Jacobian_;

	Eigen::VectorXd P_;
	Eigen::VectorXd P_s1_;

	Eigen::VectorXd Q_;
	Eigen::VectorXd Q_s1_;
	Eigen::VectorXd Q_s2_;

	//Eigen::VectorXd E;
	Eigen::VectorXd E_Integral_;
	Eigen::MatrixXd C_;
	Eigen::MatrixXd C_s1_;
	Eigen::MatrixXd C_s2_;

	Eigen::VectorXd x_;//即x_s1
	Eigen::VectorXd x_s2_;

	double dt_;
	double t_end_;
	Configuration* my_config_;
	Circuit* my_circuit_;

public:

	int size_;//矩阵维度
	vector <int> voltage_x_index_;
	vector <int> current_x_index_;

	Newton* my_newton_;
	Output* output_;

	vector<var_t> x_result_vec_;//x结果数据
	vector<var_t> plot_result_vec_;//plot结果数据
	vector<double> time_result_vec_;//time结果数据

	Eigen::MatrixXd Jacobian_;
	Eigen::VectorXd F_x0_;
	Eigen::VectorXd x_newton_;

	Solver(Configuration*, Circuit*);
	~Solver();
	void SetHint();// 对X设置初始时间步取值
	virtual void ProcessA();
	virtual void ProcessB();
	virtual void ProcessP();
	virtual void ProcessQ();
	virtual void ProcessC();
	virtual void ProcessEIntegral(double*);

	virtual void ProcessGroundedNodeEqu();
	virtual void ProcessSetZero();

	virtual void ProcessJacobianAndF() = 0;

	virtual void Solve();

	virtual void SaveResultData();

	virtual int GetSize();
};
