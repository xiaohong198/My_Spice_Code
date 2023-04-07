#pragma once
#include "Solver.h"

class Solver_TR : public Solver
{
private:
	Eigen::VectorXd E_integral;
	Eigen::VectorXd P_last;
	Eigen::MatrixXd Jacobian;
	Eigen::VectorXd F_x0;
	Eigen::VectorXd x_Newton;
	double dt_;
	double t_end_;
public:
	Solver_TR(Configuration*,Circuit*);
	~Solver_TR();

	void processExcitationDeivceMatrix(Circuit*, double, double);

	void processGroundedNodeEqu();
	void processSetZero();

	void processJacobianAndF(Configuration*, Circuit*, const Eigen::VectorXd, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double, double);

	void solve(Configuration*, Circuit*, BaseNewton*);

	void Perform_BaseNewton_solver(Configuration*, Circuit*, Solver*, Eigen::VectorXd& x_Newton, double t1, double t2);

};

