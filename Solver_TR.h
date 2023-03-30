#pragma once
#include "Solver.h"

class Solver_TR : public Solver
{
private:
	Eigen::VectorXd E_integral;
	Eigen::VectorXd P_last;
public:
	Solver_TR(Circuit*);
	~Solver_TR();

	void processExcitationDeivceMatrix(Circuit*, double, double);

	void processGroundedNodeEqu();
	void processSetZero();

	void processJacobianAndF(Configuration*, Circuit*, const Eigen::VectorXd, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double, double);

	void solve(Configuration*, Circuit*, BaseNewton*);
};

