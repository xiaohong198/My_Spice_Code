#pragma once
#include "Solver.h"

class Solver_BDF2 : public Solver
{
private:
	double a0;
	double a1;
	double a2;
public:
	Solver_BDF2(Configuration* , Circuit* );
	~Solver_BDF2();
	void getCoff();
	void processJacobianAndF();
};

