#include "BankRoseDampingNewton.h"
BankRoseDampingNewton::BankRoseDampingNewton(Solver* MySolver) : Newton(MySolver) {
	epsino = 1e-9;
	omega = 0.1;//(0,1)区间
}

void BankRoseDampingNewton::Perform_Newton() {
	double K = 0;
	Eigen::VectorXd delta_xk;
	Eigen::VectorXd xTemp;
	double Normk = 0;
	double Normkp = 0;
	double tk;
	int Iteration_times = 0;
	for (; Iteration_times < Max_Iteration_times; Iteration_times++)
	{
		xTemp = MySolver_->x_Newton;
		MySolver_->processJacobianAndF();
		Normk = MySolver_->F_x0.norm();
		delta_xk = -MySolver_->Jacobian.inverse() * MySolver_->F_x0;
		tk = 1 / (1 + K * Normk);
		MySolver_->x_Newton = MySolver_->x_Newton + tk * delta_xk;
		MySolver_->processJacobianAndF();
		Normkp = MySolver_->F_x0.norm();
		if ((1 - Normkp / Normk) / tk < omega) {
			if (K == 0) {
				K = 1;
			}
			else {
				K = 10 * K;
			}
			MySolver_->x_Newton = xTemp;
			continue;
		}
		else {
			if ((MySolver_->x_Newton - xTemp).norm() < epsino) {
				break;
			}
			else {
				K = K / 10;
			}
		}
	}
	//cout << "Iteration_times =" << Iteration_times << endl;
	_out_put_vec.push_back(Iteration_times);
}

void BankRoseDampingNewton::NewtonSave()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/BankRoseDampingNewton.txt";

	Output_ = new Output();
	Output_->SaveTxt(outputPath, _out_put_vec);
}

BankRoseDampingNewton::~BankRoseDampingNewton() {
}