#pragma once
#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "Circuit.h"
#include "Configuration.h"
#include "Newton.h"

using namespace std;

class Configuration;
class Circuit;
class Newton;

class Resistor;
class Diode;
class Vsource;
class Capacitor;
class Inductor;

class Solver
{
	friend Configuration;
	friend Resistor;
	friend Diode;
	friend Vsource;
	friend Capacitor;
	friend Inductor;
protected:
	int size;//矩阵维度
	/*
	A*x + P(x) +（B+Q(x))*dx/dt = E(t)
	Matrix:
		A
		B
		dP/dx = P_Jacobian
		dQ/dx = Q_Jacobian
		Jacobian = A + P_Jacobian + B/dt + Q_Jacobian/dt 
	Vector:
		E
		P
		Q
		F = A*x+P(x)+(B+Q(x))*dx/dt-E(t)
	*/
	Eigen::MatrixXd A;
	Eigen::MatrixXd A_mid;
	Eigen::MatrixXd B;
	Eigen::MatrixXd B_mid;

	Eigen::MatrixXd P_Jacobian;//时变电容电感
	Eigen::MatrixXd P_Jacobian_mid;//时变电容电感
	Eigen::MatrixXd Q_Jacobian;
	Eigen::MatrixXd Q_Jacobian_mid;

//	Eigen::VectorXd E;派生类Solver_EulerBackward的数据成员
	Eigen::VectorXd P;
	Eigen::VectorXd P_mid;
	Eigen::VectorXd P_last;
	Eigen::VectorXd P_last_mid;

//	Eigen::VectorXd P_last;派生类Solver_TR的数据成员
	Eigen::VectorXd Q;
	Eigen::VectorXd Q_mid;
	Eigen::VectorXd Q_last;
	Eigen::VectorXd Q_last_mid;

	Eigen::VectorXd E;
	Eigen::VectorXd E_mid;
	//Eigen::VectorXd E_integral;
	//Eigen::VectorXd E_integral_mid;

	//Eigen::VectorXd F;
	//Eigen::MatrixXd Jacobian;

	Eigen::VectorXd x;
	


	double dt_;
	double t_end_;
	Configuration* MyConfig_;
	Circuit*  MyCircuit_;

public:
	Newton* MyNewton;

	vector<Eigen::VectorXd> x_result_vec_;

	Eigen::MatrixXd Jacobian;
	Eigen::VectorXd F_x0;
	Eigen::VectorXd x_Newton;

public:
	Solver(Configuration*, Circuit*);
	~Solver();
	virtual void processSetZero();
	virtual void processSetZeroABE();
	virtual void processGroundedNodeEqu();
	virtual void processExcitationDeivceMatrix(int);
	virtual void processTimeInvariantDeviceMatrix();
	virtual void processTimeVariantDeviceMatrix();

	virtual void processJacobianAndF() = 0;

	virtual void solve() =0;

	virtual void saveCircuitVars();



};
