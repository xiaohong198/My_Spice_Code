#pragma once
//#pragma execution_character_set("utf-8")
#include <iostream>
#include <chrono>
#include "Solver/Simulator.h"
using namespace std;
#include "FastPow.h"

#if 1
int main()
{
	/*-------------PWL 电源的测试-----------*/
	//TestPWLSource();
	/*----------------------------------------*/
	Simulator MySimulator;

	auto start = std::chrono::steady_clock::now();

	MySimulator.Run();

	auto end = std::chrono::steady_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	cout << "程序用时:" << time.count() / 1000 << "毫秒" << endl;

	system("pause");

	return 0;
}
#endif // 0

#if 0
int main()
{
	/*待求解的数*/
	double x = 2.343242;

	/*求x的n次幂*/
	int n = 3;
	auto start = std::chrono::steady_clock::now();
	double result1;
	for (int i = 0; i < 9999999; i++)
	{
		result1 = std::pow(x, n);
	}
	auto end = std::chrono::steady_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "程序用时:" << time.count() / 1000 << "毫秒" << endl;

	auto start1 = std::chrono::steady_clock::now();
	double result2;
	for (int i = 0; i < 9999999; i++)
	{
		result2 = FASTPOW(x, n);
	}
	auto end1 = std::chrono::steady_clock::now();
	auto time1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
	cout << "程序用时:" << time1.count() / 1000 << "毫秒" << endl;

	std::cout << "std::pow : " << result1 << std::endl;
	std::cout << "FastPow : " << result2 << std::endl;//目前最好的

	system("pause");
	return 0;
}
#endif // 0

#if 0
#include <autodiff/forward/dual.hpp>

using namespace autodiff;
dual f(dual x)
{
	return 1 + x + x * x + 1 / x + log(x);
}

int main()
{
	dual x = 2.0;                                 // the input variable x
	dual u = f(x);                                // the output variable u

	double dudx = derivative(f, wrt(x), at(x));   // evaluate the derivative du/dx

	std::cout << "u = " << u << std::endl;        // print the evaluated output u
	std::cout << "du/dx = " << dudx << std::endl; // print the evaluated derivative du/dx
}
#endif // 0

#if 0
#include <boost/math/differentiation/autodiff.hpp>
#include <iostream>

template <typename T>
T fourth_power(T const& x) {
	T x4 = x * x;  // retval in operator*() uses x4's memory via NRVO.
	x4 *= x4;      // No copies of x4 are made within operator*=() even when squaring.
	return x4;     // x4 uses y's memory in main() via NRVO.
}

int main() {
	using namespace boost::math::differentiation;

	constexpr unsigned Order = 5;                  // Highest order derivative to be calculated.
	auto const x = make_fvar<double, Order>(2.0);  // Find derivatives at x=2.
	auto const y = fourth_power(x);
	for (unsigned i = 0; i <= Order; ++i)
		std::cout << "y.derivative(" << i << ") = " << y.derivative(i) << std::endl;
	system("pause");
	return 0;
}
#endif // 1