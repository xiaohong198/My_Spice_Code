#pragma once
#include "Newton.h"
#include <cmath>

class BasicNewton :public Newton
{
private:
	//double Convergence_limit;
	double RELTOL;
	double VNTOL;
	double ABSTOL;

public:
	BasicNewton(Solver*);
	~BasicNewton();

	void Perform_Newton();
	bool CheckConvergence();
	void NewtonSave();
};
