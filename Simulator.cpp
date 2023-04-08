#include "Simulator.h"

Simulator::Simulator() {
	MyConfig = new Configuration();
	MyCircuit = new Circuit();
	MyConfig->Set_Configuration();

	if (MyConfig->Get_TimeDiscretization() == EulerBackward) {
		MySolver = new Solver_EulerBackward(MyConfig,MyCircuit);
	}
	else if (MyConfig->Get_TimeDiscretization() == Trapezoidal) {
		MySolver = new Solver_TR(MyConfig,MyCircuit);
	}

	MyNewton = new BaseNewton(MySolver);
}

void Simulator::Run() {
	MySolver->solve(MyConfig, MyCircuit, MyNewton);
	MySolver->saveCircuitVars();

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