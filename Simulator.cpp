#include "Simulator.h"

Simulator::Simulator() {
	MyConfig = new Configuration();
	MyCircuit = new Circuit();
	//MySolver = new Solver(MyCircuit);
	MyConfig->Set_Configuration();

	if (MyConfig->Get_TimeDiscretization() == EulerBackward) {
		MySolver = new Solver_EulerBackward(MyCircuit);
	}
	else if (MyConfig->Get_TimeDiscretization() == Trapezoidal) {
		MySolver = new Solver_TR(MyCircuit);
	}

	MyNewton = new BaseNewton(MySolver);
}

void Simulator::Run() {
	MySolver->solve(MyConfig, MyCircuit, MyNewton);
}

Simulator::~Simulator() {
	delete MyConfig;
	delete MyCircuit;
	delete MySolver;
	delete MyNewton;
}