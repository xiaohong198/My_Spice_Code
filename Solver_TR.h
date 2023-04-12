#pragma once
#include "Solver.h"

class Solver_TR : public Solver
{
private:
	Eigen::VectorXd E_integral;
	Eigen::VectorXd E_integral_mid;
	Eigen::VectorXd P_last;
	Eigen::VectorXd P_last_mid;

public:
	Solver_TR(Configuration*, Circuit*);
	~Solver_TR();

	void processExcitationDeivceMatrix(double, double);

	void processGroundedNodeEqu();
	void processSetZero();

	void processJacobianAndF(const Eigen::VectorXd, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double, double);

	void solve(BaseNewton* MyNewton);

};

