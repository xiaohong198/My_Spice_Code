#include <iostream>
#include "Simulator.h"
#include <chrono>
using namespace std;

int main() {
	Simulator MySimulator;

	auto start = std::chrono::steady_clock::now();

	MySimulator.Run();

	auto end = std::chrono::steady_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	cout << "������ʱ:" << time.count()/1000 << "����" << endl;

	system("pause");

	return 0;
}