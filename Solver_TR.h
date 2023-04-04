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
public:
	Solver_TR(Configuration*, Circuit*);
	~Solver_TR();

	void processExcitationDeivceMatrix(double t1,double t2);

	void processGroundedNodeEqu();
	void processSetZero();

	void processJacobianAndF(double t1,double t2) override;

	void solve(BaseNewton*) override;
	void Perform_BaseNewton_solver(double t1, double t2);

public:
	double dt_;
	double t_end_;
	Configuration* MyConfig_;
	Circuit* MyCircuit_;
	BaseNewton* MyNewton_;
};

