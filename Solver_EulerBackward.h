#pragma once
#include "Solver.h"

class Solver_EulerBackward : public Solver
{

public:
	Solver_EulerBackward(Configuration*, Circuit*);
	~Solver_EulerBackward();

private:
	void processJacobianAndF();
	void solve(Newton* MyNewton);
	int index;

};

