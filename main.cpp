#include <iostream>
#include "Simulator.h"
#include <chrono>
#include <adolc/adolc.h>
//#include <adolc/adouble.h>
//#include <adolc/taping.h>
//#include <stdio.h>

using namespace std;

int main() {



	//// �����Ա��� x �� y
	//double x, y;

	//// �� x �� y �ֱ𸳳�ֵ
	//x = 2.0;
	//y = 3.0;
	//short i = 1;
	//short j = 2;

	//// �� tape �ϼ�¼���� f(x, y) = x^2 + y^3
	//trace_on(1,0);
	//double f = x * x + pow(y, 3.0);
	//trace_off(0);

	//// ���� f �� (x,y) = (2,3) �����ݶ�
	//double grad[2];
	//double point[2] = { 2.0, 3.0 };
	//gradient(i, j, point, grad);

	//// ������
	//cout << "f = " << f << endl;
	//cout << "grad_f = (" << grad[0] << ", " << grad[1] << ")" << endl;

	//system("pause");
	//return 0;



	Simulator MySimulator;

	auto start = std::chrono::steady_clock::now();

	MySimulator.Run();

	auto end = std::chrono::steady_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	cout << "������ʱ:" << time.count()/1000 << "����" << endl;

	system("pause");

	return 0;
}