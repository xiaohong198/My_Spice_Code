#pragma once
#include "Solver.h"

class Solver_EulerBackward : public Solver
{
private:
	Eigen::VectorXd E;
	Eigen::MatrixXd Jacobian;
	Eigen::VectorXd F_x0;
	Eigen::VectorXd x_Newton;
public:
	Solver_EulerBackward(Configuration*,Circuit*);
	~Solver_EulerBackward();

	void processExcitationDeivceMatrix(double);

	void processGroundedNodeEqu();
	void processSetZero();

	void processJacobianAndF(double t1,double t2)override;

	void solve(BaseNewton*)override;
	
	void Perform_BaseNewton_solver(double t1,double t2);
private:
	double dt_;
	double t_end_;
	Configuration* MyConfig_;
	Circuit* MyCircuit_;
	BaseNewton* MyNewton_;

};

