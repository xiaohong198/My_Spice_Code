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

//文章方法
#if 0
#include <stdio.h>
#include <math.h>

double my_sqrt(double x) {
	/* Newton's method for a square root. */
	int i = 0;
	double res = 1.0;

	if (x > 0) {
		for (i = 0; i < 10; i++) {
			res = 0.5 * (res + x / res);
		}
	}
	else {
		res = 0.0;
	}

	return res;
}

double my_152232(double x) {
	/* cubic spline interpolation for x ** 1.52232. */
	int i = 0;
	double res = 0.0;
	/* coefs[i] will give the cubic polynomial coefficients between x =
	   i and x = i+1. out of laziness, the below numbers give only a
	   linear interpolation.  you'll need to do some work and research
	   to get the spline coefficients. */

	double coefs[3][4] = { {0.0, 1.0, 0.0, 0.0},
			  {-0.872526, 1.872526, 0.0, 0.0},
			  {-2.032706, 2.452616, 0.0, 0.0} };

	if ((x >= 0) && (x < 3.0)) {
		i = (int)x;
		/* horner's method cubic. */
		res = (((coefs[i][3] * x + coefs[i][2]) * x) + coefs[i][1] * x)
			+ coefs[i][0];
	}
	else if (x >= 3.0) {
		/* scaled x ** 1.5 once you go off the spline. */
		res = 1.024824 * my_sqrt(x * x * x);
	}

	return res;
}

//double my_152232(double x) {
//	double part_050000 = my_sqrt(x);
//	double part_102232 = 1.02232 * x + 0.0114091 * x * x - 3.718147e-3 * x * x * x;
//
//	return part_102232 * part_050000;
//}
double my_019029(double x) {
	return my_sqrt(my_sqrt(my_sqrt(my_152232(x))));
}

//int main() {
//	int i;
//	double x = 0.0;
//
//	for (i = 0; i < 1000; i++) {
//		x = 1e-2 * i;
//		printf("%f %f %f \n", x, my_019029(x), pow(x, 0.19029));
//	}
//	system("pause");
//
//	return 0;
//}

double power(double x, double y)
{
	double result = 1.0;
	while (y > 0)
	{
		if (fmod(y, 2) == 1)
			result *= x;
		x *= x;
		y /= 2;
	}
	return result;
}
typedef long long ll;
ll quick_pow(ll x, ll n, ll m) {
	ll res = 1;
	while (n > 0) {
		if (n & 1)	res = res * x % m;
		x = x * x % m;
		n >>= 1;//相当于n=n/2.详情请参考位移运算符。
	}
	return res;
}

ll q_pow(ll x, ll n, ll m) {
	if (n == 0)	return 1;
	ll res = q_pow(x * x % m, n / 2, m);
	if (n & 1)	res = res * x % m;
	return res;
}
#include <cmath>
ll fq_pow(ll x, double n, ll m) {
	int p = floor(n);
	ll res = fq_pow(x, p, m);
	double np = n - p;
	res = res * fq_pow(x, np * m, m) % m;
	return res;
}

int main()
{
	/*待求解的数*/
	double x = 2.232;

	/*求x的n次幂*/
	double n = 0.2122;
	int index = 999999;

	auto start = std::chrono::steady_clock::now();
	double result1;
	for (int i = 0; i < index; i++)
	{
		result1 = pow(x, n);
	}
	auto end = std::chrono::steady_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "程序用时:" << time.count() / 1000 << "毫秒" << endl;

	auto start1 = std::chrono::steady_clock::now();
	double result2;
	for (int i = 0; i < index; i++)
	{
		result2 = fq_pow(x, n, 37);
	}
	auto end1 = std::chrono::steady_clock::now();
	auto time1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
	cout << "程序用时:" << time1.count() / 1000 << "毫秒" << endl;

	std::cout << "pow : " << result1 << std::endl;
	std::cout << "FastPow : " << result2 << std::endl;//目前最好的

	system("pause");
	return 0;
}
#endif // 0

//autodiff
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

//boost自动微分
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

//ADOL-C测试程序
#if 0
#include <adolc/adouble.h>          // use of active doubles
#include <adolc/interfaces.h>       // use of basic forward/reverse
// interfaces of ADOL-C
#include <adolc/taping.h>           // use of taping

#include <iostream>
using namespace std;

/****************************************************************************/
/*                                                          ADOUBLE ROUTINE */
int n;
adouble** A;                        // A is an n x n matrix
adouble zero = 0;

adouble det(int k, int m)           // k <= n is the order of the submatrix
{
	if (m == 0)                       // its column indices
		return 1.0;
	else                              // are encoded in m
	{
		adouble* pt = A[k - 1];
		adouble   t = zero;
		int p = 1;
		int s;
		if (k % 2)
			s = 1;
		else
			s = -1;
		for (int i = 0; i < n; i++) {
			int p1 = 2 * p;
			if (m % p1 >= p) {
				if (m == p) {
					if (s > 0)
						t += *pt;
					else
						t -= *pt;
				}
				else {
					if (s > 0)
						t += *pt * det(k - 1, m - p); // recursive call to det
					else
						t -= *pt * det(k - 1, m - p); // recursive call to det
				}
				s = -s;
			}
			++pt;
			p = p1;
		}
		return t;
	}
}

/****************************************************************************/
/*                                                             MAIN PROGRAM */
int main() {
	int i, j, m = 1;
	int tag = 1;
	int keep = 1;

	cout << "COMPUTATION OF DETERMINANTS (ADOL-C Documented Example)\n\n";
	cout << "order of matrix = ? \n"; // select matrix size
	cin >> n;

	A = new adouble * [n];
	adouble ad;

	trace_on(tag, keep);               // tag=1=keep
	double detout = 0.0, diag = 1.0;// here keep the intermediates for
	for (i = 0; i < n; i++)             // the subsequent call to reverse
	{
		m *= 2;
		A[i] = new adouble[n];
		for (j = 0; j < n; j++)
			A[i][j] <<= j / (1.0 + i);      // make all elements of A independent
		diag += A[i][i].value();       // value(adouble) converts to double
		A[i][i] += 1.0;
	}
	ad = det(n, m - 1);                // actual function call.
	ad >>= detout;
	printf("\n %f - %f = %f  (should be 0)\n", detout, diag, detout - diag);
	trace_off();

	double u[1];
	u[0] = 1.0;
	double* B = new double[n * n];

	reverse(tag, 1, n * n, 0, u, B);         // call reverse to calculate the gradient

	cout << " \n first base? : ";
	for (i = 0; i < n; i++) {
		adouble sum = 0;
		for (j = 0; j < n; j++)             // the matrix A times the first n
			sum += A[i][j] * B[j];          // components of the gradient B
		cout << sum.value() << " ";      // must be a Cartesian basis vector
	}
	cout << "\n";
	system("pause");
	return 1;
}

#endif //

//连续查找表
#if 0
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// 查找表的范围和步长
const double MIN_BASE = 0.0;
const double MAX_BASE = 10.0;
const double STEP = 0.001;

// 查找表
vector<double> pow_table;

// 初始化查找表
void init_pow_table() {
	pow_table.resize((MAX_BASE - MIN_BASE) / STEP + 1);
	for (int i = 0; i < pow_table.size(); i++) {
		double base = MIN_BASE + i * STEP;
		pow_table[i] = pow(base, 2.0);
	}
}

// 二分查找最接近底数的查找表索引
int find_index(double base) {
	int left = 0, right = pow_table.size() - 1;
	while (left < right) {
		int mid = (left + right) / 2;
		if (pow_table[mid] < base) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}
	return left;
}

// 线性插值计算幂次结果
double pow_interpolate(double base, double exponent) {
	int index = find_index(base);
	double x1 = MIN_BASE + index * STEP;
	double x2 = MIN_BASE + (index + 1) * STEP;
	double y1 = pow_table[index];
	double y2 = pow_table[index + 1];
	double slope = (y2 - y1) / (x2 - x1);
	double y = slope * (base - x1) + y1;
	return pow(y, exponent);
}

int main() {
	init_pow_table();
	double base = 3.14;
	double exponent = 2.0;
	double result = pow_interpolate(base, exponent);
	cout << "pow(" << base << ", " << exponent << ") = " << result << endl;
	return 0;
}

#endif // 0

//指数查找表
#if 0
#include <iostream>
#include <cmath>

const int TABLE_SIZE = 10000;

void createExponentTable(float base, float* table)
{
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		table[i] = std::pow(base, static_cast<float>(i) / TABLE_SIZE);
	}
}

float powerWithExponentTable(float base, float exponent, const float* table)
{
	exponent = std::fmin(std::fmax(exponent, 0.0f), 1.0f) * TABLE_SIZE;

	int index = static_cast<int>(exponent);
	float fraction = exponent - index;

	float result = table[index];

	if (index < TABLE_SIZE - 1)
	{
		float nextValue = table[index + 1];
		result = result + (nextValue - result) * fraction;
	}

	return std::pow(base, result);
}

float quadraticInterpolation(float x0, float x1, float x2, float y0, float y1, float y2, float x)
{
	float l0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2));
	float l1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2));
	float l2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1));

	return y0 * l0 + y1 * l1 + y2 * l2;
}

float powerWithQuadraticInterpolation(float base, float exponent, const float* table)
{
	exponent = std::fmin(std::fmax(exponent, 0.0f), 1.0f) * TABLE_SIZE;

	int index = static_cast<int>(exponent);
	float fraction = exponent - index;

	float x0 = static_cast<float>(index - 1);
	float x1 = static_cast<float>(index);
	float x2 = static_cast<float>(index + 1);

	float y0 = table[index - 1];
	float y1 = table[index];
	float y2 = table[index + 1];

	return std::pow(base, quadraticInterpolation(x0, x1, x2, y0, y1, y2, exponent));
}

int main()
{
	float base = 2.0f;
	float table[TABLE_SIZE];

	createExponentTable(base, table);

	float exponent = 0.75f;

	// 使用改进后的查找表方法进行幂运算
	float resultTable = powerWithExponentTable(base, exponent, table);

	// 使用pow函数进行幂运算
	float resultPow = std::pow(base, exponent);

	std::cout << "Lookup Table Result: " << resultTable << std::endl;
	std::cout << "pow() Result: " << resultPow << std::endl;

	return 0;
}

#endif // 0

//指数查找表
#if 0
#include <iostream>
#include <cmath>

// 定义查找表的大小
const int TABLE_SIZE = 1000;

// 创建指数查找表
void createExponentTable(float base, float* table)
{
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		table[i] = std::pow(base, static_cast<float>(i) / TABLE_SIZE);
	}
}

// 使用指数查找表进行幂运算
float powerWithExponentTable(float base, float exponent, const float* table)
{
	// 将指数限制在查找表的范围内
	exponent = std::fmin(std::fmax(exponent, 0.0f), 1.0f) * TABLE_SIZE;

	// 查找表的索引为整数部分
	int index = static_cast<int>(exponent);

	// 使用线性插值计算小数部分
	float fraction = exponent - index;

	// 根据索引查找查找表中的近似值
	float result = table[index];

	// 线性插值计算最终结果
	if (index < TABLE_SIZE - 1)
	{
		float nextValue = table[index + 1];
		result = result + (nextValue - result) * fraction;
	}

	return std::pow(base, result);
}

int main()
{
	float base = 2.0f;
	float table[TABLE_SIZE];

	// 创建指数查找表
	createExponentTable(base, table);

	// 测试幂运算
	float exponent = 0.75f;
	float result = powerWithExponentTable(base, exponent, table);

	std::cout << base << " ^ " << exponent << " = " << result << std::endl;

	return 0;
}

#endif // 0

//连续查找表
#if 0
#include <iostream>
#include <cmath>

using namespace std;

const double MIN_BASE = 0.0; // 查找表的最小底数
const double MAX_BASE = 1.0; // 查找表的最大底数
const double STEP = 0.01; // 查找表的步长
const int TABLE_SIZE = (MAX_BASE - MIN_BASE) / STEP + 1; // 查找表的大小

double pow_table[TABLE_SIZE]; // 存储幂次结果的查找表

// 初始化查找表
void init_pow_table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		double base = MIN_BASE + i * STEP;
		pow_table[i] = pow(base, 2.0); // 计算底数的2次幂
	}
}

// 查找最接近底数的查找表索引
int find_index(double base) {
	int index = (base - MIN_BASE) / STEP;
	if (index < 0) {
		return 0;
	}
	else if (index >= TABLE_SIZE) {
		return TABLE_SIZE - 1;
	}
	else {
		return index;
	}
}

// 线性插值计算幂次结果
double pow_interpolate(double base, double exponent) {
	int index = find_index(base);
	double x1 = MIN_BASE + index * STEP;
	double x2 = MIN_BASE + (index + 1) * STEP;
	double y1 = pow_table[index];
	double y2 = pow_table[index + 1];
	double slope = (y2 - y1) / (x2 - x1);
	double y = slope * (base - x1) + y1;
	return pow(y, exponent);
}

int main() {
	init_pow_table();
	double base = 0.35;
	double exponent = 3.0;
	double result = pow_interpolate(base, exponent);
	cout << "pow(" << base << ", " << exponent << ") = " << result << endl;
	return 0;
}

#endif // 0

#if 0
string UTF8ToGB(const char* str)
{
	string result;
	WCHAR* strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

//int main()
//{
//	double x = 10.25, result;
//	result = sqrt(x);
//	cout << UTF8ToGB("10.25的平方根是 ") << result << endl;
//	system("pause");
//	return 0;
//}

#include <iostream>
#include <cmath>
#include <chrono>    // 用于获取函数运行时间

using namespace std;

int main()
{
	volatile double a, x;
	volatile double y1, y2, y3, y4;
	a = 3.21;
	x = 3.472;
	// 记录运行的时间
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	for (int i = 0; i < 100000; i++)
	{
		y1 = sqrt(x);
	}
	chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
	for (int i = 0; i < 100000; i++)
	{
		y2 = exp(x);
	}
	chrono::steady_clock::time_point end2 = chrono::steady_clock::now();
	for (int i = 0; i < 100000; i++)
	{
		y3 = log(x);
	}
	chrono::steady_clock::time_point end3 = chrono::steady_clock::now();
	for (int i = 0; i < 100000; i++)
	{
		y4 = pow(a, x);
	}
	chrono::steady_clock::time_point end4 = chrono::steady_clock::now();
	//cout << "ln(e)" << log(2.718281828) << endl;
	//cout << "log(e)" << log10(2.718281828) << endl << endl;
	// 时间的单位为微秒
	cout << "sqrt(x)=" << y1 << UTF8ToGB("，其用时：") << chrono::duration_cast<chrono::microseconds>(end1 - begin).count() << " us" << endl;
	cout << "exp(x)=" << y2 << UTF8ToGB("，其用时：") << chrono::duration_cast<chrono::microseconds>(end2 - end1).count() << " us" << endl;
	cout << "ln(x)=" << y3 << UTF8ToGB("，其用时：") << chrono::duration_cast<chrono::microseconds>(end3 - end2).count() << " us" << endl;
	cout << "a^x=" << y4 << UTF8ToGB("，其用时：") << chrono::duration_cast<chrono::microseconds>(end4 - end3).count() << " us" << endl;
	system("pause");
	return 0;
}
//sqrt()根号
//exp()e的x次方
//ln()以e为底的对数
//log()以10为底的对数
//pow()a的x次方

//\
在关闭编译器优化的Debug-x64模式下，测得a = 3.21，x = 3.472时\
sqrt(x）、exp(x)、ln(x)、pow(a,x) 在运行一万次和十万次的运行时间\
测试时已经通过volatile方法避免了编译器对for循环中单一语句的优化\
测试结果是exp最快，pow最慢，exp和ln相差不大，但exp略快于ln\

#endif // 0