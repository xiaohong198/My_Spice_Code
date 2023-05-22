#pragma once
#include "Solver/Solver.h"
#include <cmath>
class Configuration;
class Circuit;
class Solver;

class Newton
{
public:
	int Max_Iteration_times;
	double Convergence_limit;
	Solver* MySolver_;

public:
	Newton(Solver*);
	~Newton();

	virtual void Perform_BaseNewton() = 0;
};

