#pragma once
#include "Solver/Solver.h"
enum TimeDiscretization { EulerBackward, Trapezoidal, BDF_2, SDC };
class Configuration
{
	friend class Simulator;
private:
	double dt_;
	double t_end_;
	TimeDiscretization dt_method_;

public:
	Configuration();
	~Configuration();

	double Getdt();
	double GettEnd();
	TimeDiscretization GetTimeDiscretization();

private:
	void SetConfiguration();
};
