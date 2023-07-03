#include "BasicNewton.h"

BasicNewton::BasicNewton(Solver* MySolver): Newton(MySolver) {
}

void BasicNewton::Perform_Newton()
{
	int Iteration_times = 0;
	for (; Iteration_times < Max_Iteration_times; Iteration_times++)
	{
		xk = MySolver_->x_Newton;
		MySolver_->processJacobianAndF();
		MySolver_->x_Newton = MySolver_->x_Newton - MySolver_->Jacobian.inverse() * MySolver_->F_x0;
		xkp1 = MySolver_->x_Newton;
		if (CheckConvergence()) {
			break;
		}
	}
	cout << "Iteration_times =" << Iteration_times << endl;
	//_out_put_vec.push_back(Iteration_times);
}

void BasicNewton::NewtonSave()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/BasicNewton.txt";

	Output_ = new Output();
	Output_->SaveTxt(outputPath, _out_put_vec);
}

BasicNewton::~BasicNewton() {
}