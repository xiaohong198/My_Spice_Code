#include "BankRoseDampingNewton.h"
BankRoseDampingNewton::BankRoseDampingNewton(Solver* MySolver) : Newton(MySolver) {
	epsino = 1e-9;
	omega = 0.1;//(0,1)区间
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

void BankRoseDampingNewton::Perform_Newton() {
	double K = 0;
	double tk;
	MySolver_->processJacobianAndF();//x(k)
	xk = MySolver_->x_Newton;
	Normk = MySolver_->F_x0.norm();
	delta_xk = -MySolver_->Jacobian.inverse() * MySolver_->F_x0;

	for (int Iteration_times = 0; Iteration_times < Max_Iteration_times; Iteration_times++)
	{
		while (1) {
			tk = 1.0 / (1.0 + K * Normk);
			MySolver_->x_Newton = xk + tk * delta_xk;//x_Newton����Ϊx(k+1)��
			MySolver_->processJacobianAndF();
			xkp1 = MySolver_->x_Newton;
			Normkp1 = MySolver_->F_x0.norm();
			delta_xkp1 = -MySolver_->Jacobian.inverse() * MySolver_->F_x0;
			if (1.0 / tk * (1.0 - Normkp1 / Normk) >= omega) {
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
			xk = xkp1;
			delta_xk = delta_xkp1;
			Normk = Normkp1;
			continue;
		}
	}
	//_out_put_vec.push_back(Iteration_times);
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