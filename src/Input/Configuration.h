#pragma once
#include "Solver/Solver.h"
enum TimeDiscretization { EulerBackward, Trapezoidal, BDF_2, SDC };
class Configuration
{
	friend class Simulator;
private:
	double dt;
	double t_end;
	TimeDiscretization dt_method;

public:
	Configuration();
	~Configuration();

	double Get_dt();
	double Get_t_end();
	TimeDiscretization Get_TimeDiscretization();

private:
	void Set_Configuration();
};
