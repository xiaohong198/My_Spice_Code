#pragma once
#include "SolverEulerBackward.h"
#include "SolverTR.h"
#include "SolverBDF2.h"
#include "Newton/BasicNewton.h"
#include "Newton/BankRoseDampingNewton.h"

/* 类Simulator负责整个电路求解. Simulator通过内部的Solver指针，调用实际的Solver类型去完成时间离散和求解工作.
 由于Solver类的Run函数是虚函数，真正的时间离散格式会去实现生成雅可比的工作.
*/
class Simulator
{
private:
	Configuration* my_config_;
	Circuit* my_circuit_;
	Solver* base_solver_;
	Solver* my_solver_;
	Newton* my_newton_;
public:
	Simulator();
	~Simulator();

	void Run();
};
