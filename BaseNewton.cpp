#include "BaseNewton.h"
BaseNewton::BaseNewton(Solver* MySolver) {
	Max_Iteration_times = 1000;
	Convergence_limit = 0.0001;
}

void BaseNewton::Perform_BaseNewton(Configuration* MyConfig, Circuit* MyCircuit, Solver* MySolver, Eigen::VectorXd& x_Newton, double t1, double t2) {
	int Iteration_times = 0;
	Eigen::MatrixXd Jacobian = Eigen::MatrixXd::Zero(MySolver->getSize(), MySolver->getSize());
	Eigen::VectorXd F_x0 = Eigen::VectorXd::Zero(MySolver->getSize());
	while (Iteration_times < Max_Iteration_times) {
		MySolver->processJacobianAndF(MyConfig, MyCircuit, x_Newton, Jacobian, F_x0, t1, t2);
		x_Newton = x_Newton - Jacobian.inverse() * F_x0;
		//cout << "Every Iteration x_Newton = " << endl << x_Newton << endl;
		Iteration_times++;
		if (Check_Convergence(MyConfig, MyCircuit, MySolver, F_x0)) {
			//cout << "Convergent Already! F_x0 = " << endl << F_x0 << endl;
			break;
		}
	}
	//cout << "Iteration_times " << Iteration_times << endl;
}

bool BaseNewton::Check_Convergence(Configuration* MyConfig, Circuit* MyCircuit, Solver* MySolver, Eigen::VectorXd& F_x0) {
	return ((F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false);
}

BaseNewton::~BaseNewton() {

}