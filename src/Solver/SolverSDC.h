#pragma once
#include "Solver.h"

class SolverSDC : public Solver
{
public:
	SolverSDC(Configuration*, Circuit*);
	~SolverSDC();
};
