#pragma once
#include "Solver.h"

class Solver_EulerBackward : public Solver
{
private:
	Eigen::VectorXd E;
	Eigen::MatrixXd Jacobian;
	Eigen::VectorXd F_x0;
	Eigen::VectorXd x_Newton;
	double dt_;
	double t_end_;
	Configuration* MyConfig_;
	Circuit* MyCircuit_;
public:
	Solver_EulerBackward(Configuration*,Circuit*);
	~Solver_EulerBackward();

	void processExcitationDeivceMatrix(double);

	void processGroundedNodeEqu();
	void processSetZero();

	void processJacobianAndF(const Eigen::VectorXd, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double, double);

	void solve();

	void Perform_BaseNewton_solver(Eigen::VectorXd& x_Newton, double t1, double t2);

};

