#include "BankRoseDampingNewton.h"
BankRoseDampingNewton::BankRoseDampingNewton(Solver* _my_solver) : Newton(_my_solver) {
	epsino_ = 1e-9;
	omega_ = 0.1;//(0,1)区间
}
/*--
* void BankRoseDampingNewton::Perform_Newton() {
	double K = 0;
	double tk;

	MySolver_->processJacobianAndF();//x(k)
	xk = MySolver_->x_Newton;
	Normk = MySolver_->F_x0.norm();
	delta_xk = -MySolver_->Jacobian.inverse() * MySolver_->F_x0;

	int Iteration_times = 0;
	for (Iteration_times = 0; Iteration_times < Max_Iteration_times; Iteration_times++)
	{
		tk = 1.0 / (1.0 + K * Normk);
		MySolver_->x_Newton = xk + tk * delta_xk;//x_Newton����Ϊx(k+1)��
		MySolver_->processJacobianAndF();
		xkp1 = MySolver_->x_Newton;
		Normkp1 = MySolver_->F_x0.norm();
		delta_xkp1 = -MySolver_->Jacobian.inverse() * MySolver_->F_x0;

		if (CheckConvergence()) {
			break;
		}
		else {
			if (1.0 / tk * (1.0 - Normkp1 / Normk) < omega) {
				if (K == 0) {
					K = 1;
				}
				else {
					K = 10 * K;
				}
			}
			else {
				K = K / 10;
				xk = xkp1;
				delta_xk = delta_xkp1;
				Normk = Normkp1;
			}
			continue;
		}
	}
}
*/

void BankRoseDampingNewton::PerformNewton() {
	double K = 0;
	double tk;
	my_solver_->ProcessJacobianAndF();//x(k)
	xk_ = my_solver_->x_newton_;
	normk_ = my_solver_->F_x0_.norm();
	delta_xk_ = -my_solver_->Jacobian_.inverse() * my_solver_->F_x0_;

	for (int Iteration_times = 0; Iteration_times < max_iteration_times_; Iteration_times++)
	{
		while (1) {
			tk = 1.0 / (1.0 + K * normk_);
			my_solver_->x_newton_ = xk_ + tk * delta_xk_;//x_Newton����Ϊx(k+1)��
			my_solver_->ProcessJacobianAndF();
			xkp1_ = my_solver_->x_newton_;
			normkp1_ = my_solver_->F_x0_.norm();
			delta_xkp1_ = -my_solver_->Jacobian_.inverse() * my_solver_->F_x0_;
			if (1.0 / tk * (1.0 - normkp1_ / normk_) >= omega_) {
				break;
			}
			else {
				if (K == 0) {
					K = 1;
				}
				else {
					K = 10 * K;
				}
			}
		}
		if (CheckConvergence()) {
			break;
		}
		else {
			K = K / 10;
			xk_ = xkp1_;
			delta_xk_ = delta_xkp1_;
			normk_ = normkp1_;
			continue;
		}
	}
	//_out_put_vec.push_back(Iteration_times);
}

void BankRoseDampingNewton::NewtonSave()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_path = path + "/CircuitVarsData";
	string output_path = output_dir_path + "/BankRoseDampingNewton.txt";

	output_ = new Output();
	output_->SaveTxt(output_path, out_put_vec_);
}

BankRoseDampingNewton::~BankRoseDampingNewton() {
}