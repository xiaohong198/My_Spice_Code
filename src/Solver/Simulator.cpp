#include "Simulator.h"
#include <chrono>
Simulator::Simulator() {
	MyConfig = new Configuration();
	MyCircuit = new Circuit();
	MyConfig->Set_Configuration();

	TimeDiscretization return_time = MyConfig->Get_TimeDiscretization();
	switch (return_time)
	{
	case EulerBackward:
		MySolver = new Solver_EulerBackward(MyConfig, MyCircuit);
		break;
	case Trapezoidal:
		MySolver = new Solver_TR(MyConfig, MyCircuit);
		break;
	default:
		break;
	}
	//MyNewton = new BasicNewton(MySolver);
	MyNewton = new BankRoseDampingNewton(MySolver);
	MySolver->MyNewton_ = MyNewton;
}

void Simulator::Run() {
	MySolver->solve();

	MySolver->SaveCircuitVars();

	MyNewton->NewtonSave();
}

Simulator::~Simulator() {
	delete MyConfig;
	delete MyCircuit;
	delete MySolver;
	delete MyNewton;
	MyConfig = nullptr;
	MyCircuit = nullptr;
	MySolver = nullptr;
	MyNewton = nullptr;
}