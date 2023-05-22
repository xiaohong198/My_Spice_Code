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

/* ��Simulator����������·���. Simulatorͨ���ڲ���Solverָ�룬����ʵ�ʵ�Solver����ȥ���ʱ����ɢ����⹤��.
 ����Solver���Run�������麯����������ʱ����ɢ��ʽ��ȥʵ�������ſɱȵĹ���.
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

