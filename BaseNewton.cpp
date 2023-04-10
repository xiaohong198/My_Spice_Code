#include "BaseNewton.h"
BaseNewton::BaseNewton(Solver* MySolver) {
	MySolver_ = MySolver;
	Max_Iteration_times = 1000;
	Convergence_limit = 0.0001;
}

void BaseNewton::Perform_BaseNewton(Eigen::VectorXd& x_Newton, double t1, double t2) {
	int Iteration_times = 0;
	int size = MySolver_->getSize();
	Eigen::MatrixXd Jacobian = Eigen::MatrixXd::Zero(size, size);
	Eigen::VectorXd F_x0 = Eigen::VectorXd::Zero(size);
	for (int Iteration_times = 0; Iteration_times < Max_Iteration_times; Iteration_times++)
	{
		MySolver_->processJacobianAndF(x_Newton, Jacobian, F_x0, t1, t2);
		x_Newton = x_Newton - Jacobian.inverse() * F_x0;
		//cout << "Every Iteration x_Newton = " << endl << x_Newton << endl;
		if (((F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false)) {
			//cout << "Convergent Already! F_x0 = " << endl << F_x0 << endl;
			break;
		}
	}
}

bool BaseNewton::Check_Convergence(Configuration* MyConfig, Circuit* MyCircuit, Solver* MySolver, Eigen::VectorXd& F_x0) {
	return ((F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false);
}

BaseNewton::~BaseNewton() {

}