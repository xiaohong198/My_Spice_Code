#pragma once
#include "Solver.h"

class Solver_TR : public Solver
{
private:
	Eigen::VectorXd E_integral;
	Eigen::VectorXd P_last;
public:
	Solver_TR(Configuration*, Circuit* );
	~Solver_TR();

	//void processEIntegral(Circuit*, double*);

	//void processGroundedNodeEqu();
	//void processSetZero();

	void processJacobianAndF();

	//void solve(Configuration*, Circuit*, BaseNewton*);
};
