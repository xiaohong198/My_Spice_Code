#include "Newton.h"
Newton::Newton(Solver* MySolver) {
	MySolver_ = MySolver;
	Max_Iteration_times = 100;
	AbsConvergencelimit = 1e-12;
	RELTOL = 1e-3;//ngspiceĬ��ȡ1e-3��Ϊ��߾��ȿ�ȡ1e-6
	VNTOL = 1e-6;//ngspiceĬ��ȡ1e-6��Ϊ��߾��ȿ�ȡ1e-9
	ABSTOL = 1.0e-12;
}

bool Newton::CheckConvergence() {
	//	return (((MySolver_->F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false));

	Eigen::MatrixXd xCompare(MySolver_->size, 2);
	xCompare << xk, xkp1;
	//	cout << "xk = " << endl << xk << endl;;
	//	cout << "xkp1 = " << endl << xkp1 << endl;
	//	cout << "xCompare = " << endl << xCompare << endl;
	Eigen::MatrixXd VoltageCompare = xCompare(MySolver_->VoltageXIndex, Eigen::all);
	Eigen::MatrixXd CurrentCompare = xCompare(MySolver_->CurrentXIndex, Eigen::all);
	//cout << "VoltageCompare = " << endl << VoltageCompare << endl;
	//cout << "CurrentCompare = " << endl << CurrentCompare << endl;
	//cout << "(VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() = " << endl << (VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() << endl;
	//cout << "(CurrentCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() = " << endl << (CurrentCompare.col(1) - CurrentCompare.col(0)).cwiseAbs() << endl;
	//cout << "VoltageCompare.cwiseAbs().rowwise().maxCoeff() = " << endl << VoltageCompare.cwiseAbs().rowwise().maxCoeff() << endl;
	//cout << "CurrentCompare.cwiseAbs().rowwise().maxCoeff() = " << endl << CurrentCompare.cwiseAbs().rowwise().maxCoeff() << endl;
	bool VoltageJudge = (((VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() - (RELTOL * VoltageCompare.cwiseAbs().rowwise().maxCoeff() + VNTOL * Eigen::MatrixXd::Ones(MySolver_->VoltageXIndex.size(), 1))).maxCoeff() <= 0 ? true : false);
	bool CurrentJudge = (((CurrentCompare.col(1) - CurrentCompare.col(0)).cwiseAbs() - (RELTOL * CurrentCompare.cwiseAbs().rowwise().maxCoeff() + ABSTOL * Eigen::MatrixXd::Ones(MySolver_->CurrentXIndex.size(), 1))).maxCoeff() <= 0 ? true : false);
	//cout << "((VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() - (RELTOL * VoltageCompare.cwiseAbs().rowwise().maxCoeff() + VNTOL * Eigen::MatrixXd::Ones(MySolver_->VoltageXIndex.size(), 1)))" << endl << ((VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() - (RELTOL * VoltageCompare.cwiseAbs().rowwise().maxCoeff() + VNTOL * Eigen::MatrixXd::Ones(MySolver_->VoltageXIndex.size(), 1))) << endl;
	//cout << "((CurrentCompare.col(1) - CurrentCompare.col(0)).cwiseAbs() - (RELTOL * CurrentCompare.rowwise().cwiseAbs().maxCoeff() + ABSTOL * Eigen::MatrixXd::Ones(MySolver_->CurrentXIndex.size(), 1)))" << endl << ((CurrentCompare.col(1) - CurrentCompare.col(0)).cwiseAbs() - (RELTOL * CurrentCompare.cwiseAbs().rowwise().maxCoeff() + ABSTOL * Eigen::MatrixXd::Ones(MySolver_->CurrentXIndex.size(), 1))) << endl;

//	cout << "VoltageJudge = " << VoltageJudge << endl;
//	cout << "CurrentJudge = " << CurrentJudge << endl;

	bool AbsFxJudge = (MySolver_->F_x0.cwiseAbs().maxCoeff() < AbsConvergencelimit);
	//	cout << "AbsFx = " << endl << MySolver_->F_x0.cwiseAbs() << endl;
	//	cout << "AbsFxJudge = " << AbsFxJudge << endl;
	return (VoltageJudge && CurrentJudge && AbsFxJudge);
	//return (AbsFxJudge);
}

Newton::~Newton() {
}