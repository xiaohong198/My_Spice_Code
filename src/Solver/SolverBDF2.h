#pragma once
#include "Solver.h"

class SolverBDF2 : public Solver
{
private:
	double a0_;
	double a1_;
	double a2_;
public:
	SolverBDF2(Configuration*, Circuit*);
	~SolverBDF2();
	void GetCoff();
	void ProcessJacobianAndF();
};
