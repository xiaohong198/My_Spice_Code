#pragma once
#include "Solver.h"

class Solver_EulerBackward : public Solver
{
private:
	Eigen::VectorXd E;
public:
	Solver_EulerBackward(Circuit*);
	~Solver_EulerBackward();

	void processExcitationDeivceMatrix(Circuit*, double);

	void processGroundedNodeEqu();
	void processSetZero();

	void processJacobianAndF(Configuration*, Circuit*, const Eigen::VectorXd, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double, double);

	void solve(Configuration*, Circuit*, BaseNewton*);
};

