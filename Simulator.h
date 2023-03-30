#pragma once
#include "Solver_EulerBackward.h"
#include "Solver_TR.h"
#include "Solver_SDC.h"

class Circuit;
class Solver;
class Solver_EulerBackward;
class Solver_TR;
class Solver_SDC;
class Configuration;
class BaseNewton;

/* ��Simulator����������·���. Simulatorͨ���ڲ���Solverָ�룬����ʵ�ʵ�Solver����ȥ���ʱ����ɢ����⹤��.
 ����Solver���Run�������麯����������ʱ����ɢ��ʽ��ȥʵ�������ſɱȵĹ���.
*/
class Simulator
{
private:
	Configuration* MyConfig;
	Circuit* MyCircuit;
	Solver* MySolver;
	BaseNewton* MyNewton;
public:
	Simulator();
	~Simulator();

	void Run();
};

