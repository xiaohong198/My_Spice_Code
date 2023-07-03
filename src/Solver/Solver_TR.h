#pragma once
#include "Solver.h"

class Solver_TR : public Solver
{
public:
	Solver_TR(Configuration*, Circuit*);
	~Solver_TR();

	void processJacobianAndF();
};
