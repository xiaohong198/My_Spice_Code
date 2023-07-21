#pragma once
#include "Solver.h"

class SolverEulerBackward : public Solver
{
public:
	SolverEulerBackward(Configuration*, Circuit*);
	~SolverEulerBackward();
	void ProcessJacobianAndF();
};
