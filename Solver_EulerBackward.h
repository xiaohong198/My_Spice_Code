#pragma once
#include "Solver.h"

class Solver_EulerBackward : public Solver
{
private:
	Eigen::VectorXd E;
	Eigen::VectorXd E_mid;

public:
	Solver_EulerBackward(Configuration*,Circuit*);
	~Solver_EulerBackward();

	void processExcitationDeivceMatrix(double);

	void processGroundedNodeEqu();
	void processSetZero();
	void processSetZeroABE();
	void processJacobianAndF(const Eigen::VectorXd, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double, double);

	void solve(BaseNewton* MyNewton);

};

