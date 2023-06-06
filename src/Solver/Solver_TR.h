#pragma once
#include "Solver.h"

class Solver_TR : public Solver
{
private:
	//Eigen::VectorXd E_integral;
	//Eigen::VectorXd P_last;
	//Eigen::VectorXd C_last;
public:
	Solver_TR(Configuration*, Circuit* );
	~Solver_TR();

	void processJacobianAndF();

};
