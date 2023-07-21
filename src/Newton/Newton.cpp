#include "Newton.h"
Newton::Newton(Solver* _my_solver) {
	my_solver_ = _my_solver;
	max_iteration_times_ = 100;
	abs_convergence_limit_ = 1e-12;
	RELTOL_ = 1e-3;//ngspiceĬ��ȡ1e-3��Ϊ��߾��ȿ�ȡ1e-6
	VNTOL_ = 1e-6;//ngspiceĬ��ȡ1e-6��Ϊ��߾��ȿ�ȡ1e-9
	ABSTOL_ = 1.0e-12;
}

bool Newton::CheckConvergence() {
	//	return (((MySolver_->F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false));

	Eigen::MatrixXd x_compare(my_solver_->size_, 2);
	x_compare << xk_, xkp1_;
	//	cout << "xk = " << endl << xk << endl;;
	//	cout << "xkp1 = " << endl << xkp1 << endl;
	//	cout << "xCompare = " << endl << xCompare << endl;
	Eigen::MatrixXd voltage_compare = x_compare(my_solver_->voltage_x_index_, Eigen::all);
	Eigen::MatrixXd current_compare = x_compare(my_solver_->current_x_index_, Eigen::all);
	//cout << "VoltageCompare = " << endl << VoltageCompare << endl;
	//cout << "CurrentCompare = " << endl << CurrentCompare << endl;
	//cout << "(VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() = " << endl << (VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() << endl;
	//cout << "(CurrentCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() = " << endl << (CurrentCompare.col(1) - CurrentCompare.col(0)).cwiseAbs() << endl;
	//cout << "VoltageCompare.cwiseAbs().rowwise().maxCoeff() = " << endl << VoltageCompare.cwiseAbs().rowwise().maxCoeff() << endl;
	//cout << "CurrentCompare.cwiseAbs().rowwise().maxCoeff() = " << endl << CurrentCompare.cwiseAbs().rowwise().maxCoeff() << endl;
	bool voltage_judge = (((voltage_compare.col(1) - voltage_compare.col(0)).cwiseAbs() - (RELTOL_ * voltage_compare.cwiseAbs().rowwise().maxCoeff() + VNTOL_ * Eigen::MatrixXd::Ones(my_solver_->voltage_x_index_.size(), 1))).maxCoeff() <= 0 ? true : false);
	bool current_judge = (((current_compare.col(1) - current_compare.col(0)).cwiseAbs() - (RELTOL_ * current_compare.cwiseAbs().rowwise().maxCoeff() + ABSTOL_ * Eigen::MatrixXd::Ones(my_solver_->current_x_index_.size(), 1))).maxCoeff() <= 0 ? true : false);
	//cout << "((VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() - (RELTOL * VoltageCompare.cwiseAbs().rowwise().maxCoeff() + VNTOL * Eigen::MatrixXd::Ones(MySolver_->VoltageXIndex.size(), 1)))" << endl << ((VoltageCompare.col(1) - VoltageCompare.col(0)).cwiseAbs() - (RELTOL * VoltageCompare.cwiseAbs().rowwise().maxCoeff() + VNTOL * Eigen::MatrixXd::Ones(MySolver_->VoltageXIndex.size(), 1))) << endl;
	//cout << "((CurrentCompare.col(1) - CurrentCompare.col(0)).cwiseAbs() - (RELTOL * CurrentCompare.rowwise().cwiseAbs().maxCoeff() + ABSTOL * Eigen::MatrixXd::Ones(MySolver_->CurrentXIndex.size(), 1)))" << endl << ((CurrentCompare.col(1) - CurrentCompare.col(0)).cwiseAbs() - (RELTOL * CurrentCompare.cwiseAbs().rowwise().maxCoeff() + ABSTOL * Eigen::MatrixXd::Ones(MySolver_->CurrentXIndex.size(), 1))) << endl;

//	cout << "VoltageJudge = " << VoltageJudge << endl;
//	cout << "CurrentJudge = " << CurrentJudge << endl;

	bool abs_fx_judge = (my_solver_->F_x0_.cwiseAbs().maxCoeff() < abs_convergence_limit_);
	//	cout << "AbsFx = " << endl << MySolver_->F_x0.cwiseAbs() << endl;
	//	cout << "AbsFxJudge = " << AbsFxJudge << endl;
	return (voltage_judge && current_judge && abs_fx_judge);
	//return (AbsFxJudge);
}

Newton::~Newton() {
}