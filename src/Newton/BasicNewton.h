#pragma once
#include "Newton.h"
#include <cmath>

class BasicNewton :public Newton
{
public:
	BasicNewton(Solver*);
	~BasicNewton();

	void PerformNewton();
	void NewtonSave();
};
