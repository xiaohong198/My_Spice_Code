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
	MyNewton = new BasicNewton(MySolver);
}

void Simulator::Run() {
	//auto start = std::chrono::steady_clock::now();

	MySolver->solve(MyNewton);

	//auto end = std::chrono::steady_clock::now();

	//auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//cout << "程序用时:" << time.count() / 1000 << "毫秒" << endl;

	//auto start2 = std::chrono::steady_clock::now();

	MySolver->saveCircuitVars();

	//auto end2 = std::chrono::steady_clock::now();

	//auto time2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);

	//cout << "程序用时:" << time2.count() / 1000 << "毫秒" << endl;
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