#include "Solver_EulerBackward.h"
Solver_EulerBackward::Solver_EulerBackward(Configuration* MyConfig, Circuit* MyCircuit) :Solver(MyConfig, MyCircuit) {
}
void Solver_EulerBackward::processJacobianAndF() {
	processSetZero();//每个牛顿迭代之前先把P、Q、P_Jacobian、Q_Jacobian、C矩阵清零
	processP();
	processQ();
	processC();
	processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��
	F_x0 = (A * x_Newton + P) * dt_ + (B + C) * (x_Newton - x) + (Q - Q_s1) - E_Integral;
	Jacobian = (A + P_Jacobian) * dt_ + B + C + Q_Jacobian;
}

Solver_EulerBackward::~Solver_EulerBackward() {
}