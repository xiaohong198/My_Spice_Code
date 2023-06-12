#pragma once
#include "Newton\Newton.h"
#include <cmath>
class BankRoseDampingNewton :public Newton
{
private:
	double epsino;
	double omega;
public:
	BankRoseDampingNewton(Solver*);
	~BankRoseDampingNewton();

	void Perform_Newton();
	void NewtonSave();
};
