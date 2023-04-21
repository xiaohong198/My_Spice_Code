#include <iostream>
#include <cmath>
#include "Simulator.h"
#include <chrono>
//#include <adolc/adolc.h>
//#include <adolc/adouble.h>
//#include <adolc/taping.h>
//#include <stdio.h>

using namespace std;
//void TestPWLSource();
int main() {
	/*-------------PWL 电源的测试-----------*/
	//TestPWLSource();
	/*----------------------------------------*/
	Simulator MySimulator;

	auto start = std::chrono::steady_clock::now();

	MySimulator.Run();

	auto end = std::chrono::steady_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	cout << "程序用时:" << time.count()/1000 << "毫秒" << endl;

	system("pause");

	return 0;
}

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
		double tList[2] = { i * dt ,(i + 1) * dt };
		//t = i * dt;
		//tplus = (i + 1) * dt;
		Vout[i] = MyPWL.eFunction(t);
		VInteg[i] = MyPWL.setIntegration(tList);
	}
	std::ofstream Vout_vars("../spice0/CircuitVarsData/TestPWLVout.txt", std::ios::trunc | std::ios::out);
//	std::ofstream Vout_vars("../spice0/CircuitVarsData/TestPWLVout.txt", std::ios::app);
	std::ofstream VInteg_vars("../spice0/CircuitVarsData/TestPWLVinteg.txt", std::ios::trunc | std::ios::out);
//	std::ofstream VInteg_vars("../spice0/CircuitVarsData/TestPWLVinteg.txt", std::ios::app);
	for (int i = 0; i < 1000; i++)
	{
		//Vout_vars << std::setprecision(8) << Vout[i] << ',';
		//VInteg_vars << std::setprecision(8) << VInteg[i] << ',';
		Vout_vars << Vout[i] << endl;
		VInteg_vars << VInteg[i] << endl;
	}
	Vout_vars << std::endl;
	Vout_vars.close();
	VInteg_vars << std::endl;
	VInteg_vars.close();
}