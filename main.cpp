#include <iostream>
#include "Simulator.h"
#include <chrono>
#include <adolc/adolc.h>
//#include <adolc/adouble.h>
//#include <adolc/taping.h>
//#include <stdio.h>

using namespace std;

int main() {



	//// 定义自变量 x 和 y
	//double x, y;

	//// 对 x 和 y 分别赋初值
	//x = 2.0;
	//y = 3.0;
	//short i = 1;
	//short j = 2;

	//// 在 tape 上记录函数 f(x, y) = x^2 + y^3
	//trace_on(1,0);
	//double f = x * x + pow(y, 3.0);
	//trace_off(0);

	//// 计算 f 在 (x,y) = (2,3) 处的梯度
	//double grad[2];
	//double point[2] = { 2.0, 3.0 };
	//gradient(i, j, point, grad);

	//// 输出结果
	//cout << "f = " << f << endl;
	//cout << "grad_f = (" << grad[0] << ", " << grad[1] << ")" << endl;

	//system("pause");
	//return 0;



	Simulator MySimulator;

	auto start = std::chrono::steady_clock::now();

	MySimulator.Run();

	auto end = std::chrono::steady_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	cout << "程序用时:" << time.count()/1000 << "毫秒" << endl;

	system("pause");

	return 0;
}