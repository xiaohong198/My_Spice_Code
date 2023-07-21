#pragma once
#include "Newton\Newton.h"
#include <cmath>
class BankRoseDampingNewton :public Newton
{
private:
	double epsino_;
	double omega_;
public:
	BankRoseDampingNewton(Solver*);
	~BankRoseDampingNewton();

	void PerformNewton();
	void NewtonSave();
};
