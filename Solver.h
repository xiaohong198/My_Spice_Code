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
#include "BaseNewton.h"

using namespace std;

class Configuration;
class Circuit;
class BaseNewton;

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
	Eigen::MatrixXd B;
	Eigen::MatrixXd P_Jacobian;//时变电容电感
	Eigen::MatrixXd Q_Jacobian;

//	Eigen::VectorXd E;派生类Solver_EulerBackward的数据成员
	Eigen::VectorXd P;
//	Eigen::VectorXd P_last;派生类Solver_TR的数据成员
	Eigen::VectorXd Q;
	Eigen::VectorXd Q_last;

	//Eigen::VectorXd F;
	//Eigen::MatrixXd Jacobian;

	Eigen::VectorXd x;

public:
	vector<Eigen::VectorXd> x_result_vec_;


public:
	Solver();
	~Solver();

	virtual void processTimeInvariantDeviceMatrix(Circuit*);
	virtual void processTimeVariantDeviceMatrix(Circuit*, const Eigen::VectorXd& x_pr);
	virtual void processExcitationDeivceMatrix(int);

	virtual void processGroundedNodeEqu() = 0;
	virtual void processSetZero() = 0;

	virtual void processJacobianAndF(double t1 ,double t2) = 0;

	virtual void solve(BaseNewton*) =0;

	virtual void saveCircuitVars();

	virtual int getSize();
};

