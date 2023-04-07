#include "Simulator.h"

Simulator::Simulator() {
	MyConfig = new Configuration();
	MyCircuit = new Circuit();
	//MySolver = new Solver(MyCircuit);
	MyConfig->Set_Configuration();

	if (MyConfig->Get_TimeDiscretization() == EulerBackward) {
		// ����и���ʼ��������solver�ĸ��ֲ�������x�����ѭ��
		MySolver = new Solver_EulerBackward(MyConfig,MyCircuit);
	}
	else if (MyConfig->Get_TimeDiscretization() == Trapezoidal) {
		MySolver = new Solver_TR(MyConfig, MyCircuit);
	}

	MyNewton = new BaseNewton(MySolver);
}

void Simulator::Run() {
	//02
	//03-09
	MySolver->solve(MyNewton);
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