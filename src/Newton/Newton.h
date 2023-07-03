#pragma once
#include "Solver/Solver.h"
#include <cmath>
#include <Eigen/Dense>
#include <Output/Output.h>
class Configuration;
class Circuit;
class Solver;
class Newton
{
protected:
	double AbsConvergencelimit;
	double RELTOL;
	double VNTOL;
	double ABSTOL;

	Eigen::VectorXd xk;
	Eigen::VectorXd delta_xk;
	double Normk;
	Eigen::VectorXd xkp1;
	Eigen::VectorXd delta_xkp1;
	double Normkp1;

public:
	Solver* MySolver_;
	Output* Output_;
	int Max_Iteration_times;
	vector<var_t> _out_put_vec;

public:
	Newton(Solver*);
	~Newton();
	virtual bool CheckConvergence();
	virtual void Perform_Newton() = 0;
	virtual void NewtonSave() = 0;
};
