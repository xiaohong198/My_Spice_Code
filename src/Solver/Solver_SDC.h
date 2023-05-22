#pragma once
#include "Solver.h"

class Solver_SDC : public Solver
{
public:
	Solver_SDC(Configuration* , Circuit* );
	~Solver_SDC();
};

