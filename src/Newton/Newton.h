#pragma once
#include "Solver/Solver.h"
#include <cmath>
#include <Eigen/Dense>
#include "Output/Output.h"
class Configuration;
class Circuit;
class Solver;
class Newton
{
public:
	Solver* MySolver_;
	Output* Output_;
	int Max_Iteration_times;
	vector<var_t> _out_put_vec;

public:
	Newton(Solver*);
	~Newton();

	virtual void Perform_Newton() = 0;
	virtual void NewtonSave() = 0;
};
