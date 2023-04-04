#include <iostream>
#include "Simulator.h"
#include <chrono>
#include <list>
#include <algorithm>
#include "PWLVoltageSource.h"
using namespace std;




void TestPWLSource() {
	double tend = 5.0e-6;
	int N = 1000;
	double dt = tend / N;
	double t = 0;
	double tplus;
	double Vout[1000] = { 0 };
	double VInteg[1000] = { 0 };
	PWLVoltageSource MyPWL;
	for (int i = 0; i < 1000; i++) {
		t = i * dt;
		tplus = (i + 1) * dt;
		Vout[i] = MyPWL.eFunction(t);
		cout << Vout[i] << endl;
		VInteg[i] = MyPWL.setIntegration(t, tplus);
	}
	std::ofstream Vout_vars("../spice0/CircuitVarsData/TestPWLVout.txt", std::ios::trunc | std::ios::out);
	// std::ofstream Vout_vars("../spice0/CircuitVarsData/TestPWLVout.txt", std::ios::app);
	std::ofstream VInteg_vars("../spice0/CircuitVarsData/TestPWLVinteg.txt", std::ios::trunc | std::ios::out);
	// std::ofstream VInteg_vars("../spice0/CircuitVarsData/TestPWLVinteg.txt", std::ios::app);
	for (int i = 0; i < 1000; i++)
	{
		Vout_vars << std::setprecision(8) << Vout[i] << ',';
		VInteg_vars << std::setprecision(8) << VInteg[i] << ',';
	}
	Vout_vars << std::endl;
	Vout_vars.close();
	VInteg_vars << std::endl;
	VInteg_vars.close();
}




int main() {


#if 0
	TestPWLSource();

	system("pause");

	return 0;
#endif // 0


#if 0
	cout << (float)0.9e-6;
	PWLVoltageSource *test = new PWLVoltageSource();
	test->eFunction(1.0e-6);
	test->setIntegration(0.00000001, 0.000002);

	system("pause");
	return 0;
#endif // 0

	Simulator MySimulator;

	auto start = std::chrono::steady_clock::now();

	//01
	MySimulator.Run();

	auto end = std::chrono::steady_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	cout << "³ÌÐòÓÃÊ±:" << time.count()/1000 << "ºÁÃë" << endl;

	system("pause");

	return 0;
}