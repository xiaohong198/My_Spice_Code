#pragma once
#include "Solver.h"

class SolverTR : public Solver
{
public:
	SolverTR(Configuration*, Circuit*);
	~SolverTR();

	void ProcessJacobianAndF();
};
