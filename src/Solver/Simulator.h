#pragma once
#include "Solver_EulerBackward.h"
#include "Solver_TR.h"
#include "Solver_SDC.h"
#include "Newton\BasicNewton.h"

class Circuit;
class Solver;
class Solver_EulerBackward;
class Solver_TR;
class Solver_SDC;
class Configuration;
class Newton;
class BasicNewton;

/* 类Simulator负责整个电路求解. Simulator通过内部的Solver指针，调用实际的Solver类型去完成时间离散和求解工作.
 由于Solver类的Run函数是虚函数，真正的时间离散格式会去实现生成雅可比的工作.
*/
class Simulator
{
private:
	Configuration* MyConfig;
	Circuit* MyCircuit;
	Solver* BaseSolver;
	Solver* MySolver;
	Newton* MyNewton;
public:
	Simulator();
	~Simulator();

	void Run();
};

