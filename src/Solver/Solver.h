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
#include "FastPow.h"
using namespace std;
class Newton;
class Solver
{
protected:

	Eigen::MatrixXd A;
	Eigen::MatrixXd B;

	Eigen::MatrixXd P_Jacobian;//时变电容电感
	Eigen::MatrixXd Q_Jacobian;

	Eigen::VectorXd P;
	Eigen::VectorXd P_last;

	Eigen::VectorXd Q;
	Eigen::VectorXd Q_last;

	//Eigen::VectorXd E;
	Eigen::VectorXd E_Integral;
	Eigen::MatrixXd C;
	Eigen::MatrixXd C_last;

	Eigen::VectorXd x;

	double dt_;
	double t_end_;
	Configuration* MyConfig_;
	Circuit* MyCircuit_;

public:
	int size;//矩阵维度
	vector <int> VoltageXIndex;
	vector <int> CurrentXIndex;

	Newton* MyNewton_;
	Output* Output_;

	vector<var_t> x_result_vec_;

	Eigen::MatrixXd Jacobian;
	Eigen::VectorXd F_x0;
	Eigen::VectorXd x_Newton;
	Eigen::VectorXd x_Newton_pr;

	Solver(Configuration*, Circuit*);
	~Solver();
	virtual void processA();
	virtual void processB();
	virtual void processP();
	virtual void processQ();
	virtual void processC();
	virtual void processEIntegral(double*);

	virtual void processGroundedNodeEqu();
	virtual void processSetZero();

	virtual void processJacobianAndF() = 0;

	virtual void solve();

	virtual void SaveCircuitVars();

	virtual int getSize();
};
