#include "BasicNewton.h"

BasicNewton::BasicNewton(Solver* _my_solver) : Newton(_my_solver) {
}

void BasicNewton::PerformNewton()
{
	int iteration_times = 0;
	for (; iteration_times < max_iteration_times_; iteration_times++)
	{
		xk_ = my_solver_->x_newton_;
		my_solver_->ProcessJacobianAndF();
		my_solver_->x_newton_ = my_solver_->x_newton_ - my_solver_->Jacobian_.inverse() * my_solver_->F_x0_;
		xkp1_ = my_solver_->x_newton_;
		if (CheckConvergence()) {
			break;
		}
	}
	//cout << "Iteration_times =" << Iteration_times << endl;
	//_out_put_vec.push_back(Iteration_times);
}

void BasicNewton::NewtonSave()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_path = path + "/CircuitVarsData";
	string output_path = output_dir_path + "/BasicNewton.txt";

	output_ = new Output();
	output_->SaveTxt(output_path, out_put_vec_);
}

BasicNewton::~BasicNewton() {
}