#pragma once
#include "Solver.h"

class Solver_EulerBackward : public Solver
{
public:
	Solver_EulerBackward(Configuration*, Circuit* );
	~Solver_EulerBackward();
	void processJacobianAndF();

};

