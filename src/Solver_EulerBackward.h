#pragma once
#include "Solver.h"

class Solver_EulerBackward : public Solver
{
//private:
//	Eigen::VectorXd E;
public:
	Solver_EulerBackward(Configuration*, Circuit* );
	~Solver_EulerBackward();

	//void processEIntegral(Circuit*, double*);

	//void processGroundedNodeEqu();
	//void processSetZero();

	void processJacobianAndF();

	//void solve(Configuration*, Circuit*, BaseNewton*);
};

