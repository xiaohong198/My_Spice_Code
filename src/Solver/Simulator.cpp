#include "Simulator.h"
#include <chrono>
Simulator::Simulator() {
	my_config_ = new Configuration();
	my_circuit_ = new Circuit();
	my_config_->SetConfiguration();

	TimeDiscretization return_time = my_config_->GetTimeDiscretization();
	switch (return_time)
	{
	case EulerBackward:
		my_solver_ = new SolverEulerBackward(my_config_, my_circuit_);
		break;
	case Trapezoidal:
		my_solver_ = new SolverTR(my_config_, my_circuit_);
		break;
	case BDF_2:
		my_solver_ = new SolverBDF2(my_config_, my_circuit_);
		break;
	default:
		break;
	}
	my_newton_ = new BasicNewton(my_solver_);
	//MyNewton = new BankRoseDampingNewton(MySolver);
	my_solver_->my_newton_ = my_newton_;
}

void Simulator::Run() {
	my_solver_->Solve();

	my_solver_->SaveResultData();

	my_newton_->NewtonSave();
}

Simulator::~Simulator() {
	delete my_config_;
	delete my_circuit_;
	delete my_solver_;
	delete my_newton_;
	my_config_ = nullptr;
	my_circuit_ = nullptr;
	my_solver_ = nullptr;
	my_newton_ = nullptr;
}