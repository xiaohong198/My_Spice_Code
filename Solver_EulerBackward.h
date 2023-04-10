#pragma once
#include "Solver.h"

class Solver_EulerBackward : public Solver
{
private:
	Eigen::VectorXd E;

public:
	Solver_EulerBackward(Configuration*,Circuit*);
	~Solver_EulerBackward();

	void processExcitationDeivceMatrix(double);

	void processGroundedNodeEqu();
	void processSetZero();

	void processJacobianAndF(const Eigen::VectorXd, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double, double);

	void solve(BaseNewton* MyNewton);

	void Perform_BaseNewton_solver(Eigen::VectorXd& x_Newton, double t1, double t2);

};

