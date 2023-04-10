#pragma once
#include "Solver.h"
#include <cmath>
class Configuration;
class Circuit;
class Solver;

class BaseNewton
{
private:
	int Max_Iteration_times;
	double Convergence_limit;
	Solver* MySolver_;
public:
	BaseNewton(Solver*);
	~BaseNewton();

	void Perform_BaseNewton(Eigen::VectorXd& x_Newton, double t1, double t2);
	bool Check_Convergence(Configuration*, Circuit*, Solver*, Eigen::VectorXd& F_x0);
};

