#include "BasicNewton.h"
BasicNewton::BasicNewton(Solver* MySolver): Newton(MySolver) {
	//Convergence_limit = 1.0e-9;//1.0e-4
	RELTOL = 1e-3;//ngspice默认取1e-3
	VNTOL = 1e-6;//ngspice默认取1e-6
	ABSTOL = 1.0e-12;
}

bool BasicNewton::CheckConvergence() {

	Eigen::MatrixXd xCompare(MySolver_->size, 2);
	xCompare << MySolver_->x_Newton_pr, MySolver_->x_Newton;
	Eigen::MatrixXd VoltageCompare = xCompare(MySolver_->VoltageXIndex, Eigen::all);
	Eigen::MatrixXd CurrentCompare = xCompare(MySolver_->CurrentXIndex, Eigen::all);
	bool VoltageJudge = (((VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() - (RELTOL * VoltageCompare.cwiseAbs().rowwise().maxCoeff() + VNTOL * Eigen::MatrixXd::Ones(MySolver_->VoltageXIndex.size(), 1))).maxCoeff() <= 0 ? true : false);
	bool CurrentJudge = (((CurrentCompare.col(1) - CurrentCompare.col(0)).cwiseAbs() - (RELTOL * CurrentCompare.cwiseAbs().rowwise().maxCoeff() + ABSTOL * Eigen::MatrixXd::Ones(MySolver_->CurrentXIndex.size(), 1))).maxCoeff() <= 0 ? true : false);
	return (VoltageJudge && CurrentJudge);
}

void BasicNewton::Perform_Newton()
{
	int Iteration_times = 0;
	for (; Iteration_times < Max_Iteration_times; Iteration_times++)
	{
		MySolver_->x_Newton_pr = MySolver_->x_Newton;
		MySolver_->processJacobianAndF();
		MySolver_->x_Newton = MySolver_->x_Newton - MySolver_->Jacobian.inverse() * MySolver_->F_x0;
		 
		if (CheckConvergence()) {
			break;
		}
	}
	_out_put_vec.push_back(Iteration_times);
}

void BasicNewton::NewtonSave()
{	
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/BasicNewton.txt";

	Output_= new Output();
	Output_->SaveTxt(outputPath, _out_put_vec);
}

BasicNewton::~BasicNewton() {

}