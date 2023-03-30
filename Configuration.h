#pragma once
enum TimeDiscretization { EulerBackward, Trapezoidal, BDF_2, SDC };
#include "Solver.h"
class Configuration
{
	friend class Simulator;
private:
	double dt;
	double t_end;
	TimeDiscretization dt_method;

public:
	Configuration();
	void Set_Configuration();
	double Get_dt();
	double Get_t_end();
	TimeDiscretization Get_TimeDiscretization();

	~Configuration();
};

