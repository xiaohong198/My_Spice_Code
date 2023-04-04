#include "BaseNewton.h"
BaseNewton::BaseNewton(Solver* MySolver) {
	Max_Iteration_times = 1000;
	Convergence_limit = 0.0001;
}
#include <chrono>
//04-EulerBackward-Trapezoidal
void BaseNewton::Perform_BaseNewton(Configuration* MyConfig, Circuit* MyCircuit, Solver* MySolver, Eigen::VectorXd& x_Newton, double t1, double t2) {
	//auto start = std::chrono::steady_clock::now();

	int Iteration_times = 0;
	Eigen::MatrixXd Jacobian = Eigen::MatrixXd::Zero(MySolver->getSize(), MySolver->getSize());
	Eigen::VectorXd F_x0 = Eigen::VectorXd::Zero(MySolver->getSize());
	//循环-02
	while (Iteration_times < Max_Iteration_times) {
		//05-08-EulerBackward-Trapezoidal
		//循环-03-05
		MySolver->processJacobianAndF(t1, t2);
		x_Newton = x_Newton - Jacobian.inverse() * F_x0;
		//cout << "Every Iteration x_Newton = " << endl << x_Newton << endl;
		Iteration_times++;
		//09-EulerBackward-Trapezoidal
		if (Check_Convergence(MyConfig, MyCircuit, MySolver, F_x0)) {
			//cout << "Convergent Already! F_x0 = " << endl << F_x0 << endl;
			break;
		}
	}
	//auto end = std::chrono::steady_clock::now();

	//auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//cout << "Perform_BaseNewton程序用时:" << time.count() / 1000 << "毫秒" << endl;


	//cout << "Iteration_times " << Iteration_times << endl;
}
//09-EulerBackward-Trapezoidal
bool BaseNewton::Check_Convergence(Configuration* MyConfig, Circuit* MyCircuit, Solver* MySolver, Eigen::VectorXd& F_x0) {
	return ((F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false);
}

BaseNewton::~BaseNewton() {

}