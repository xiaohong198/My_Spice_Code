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
	double abs_convergence_limit_;
	double RELTOL_;
	double VNTOL_;
	double ABSTOL_;

	Eigen::VectorXd xk_;
	Eigen::VectorXd delta_xk_;
	Eigen::VectorXd xkp1_;
	Eigen::VectorXd delta_xkp1_;
	double normk_;
	double normkp1_;

public:
	Solver* my_solver_;
	Output* output_;
	int max_iteration_times_;
	vector<var_t> out_put_vec_;

public:
	Newton(Solver*);
	~Newton();
	virtual bool CheckConvergence();
	virtual void PerformNewton() = 0;
	virtual void NewtonSave() = 0;
};
