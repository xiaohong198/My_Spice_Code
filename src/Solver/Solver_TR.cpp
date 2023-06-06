#include "Solver_TR.h"
Solver_TR::Solver_TR(Configuration* MyConfig, Circuit* MyCircuit) :Solver(MyConfig, MyCircuit) {
}
Solver_TR::~Solver_TR() {

}

void Solver_TR::processJacobianAndF() {
    processSetZero();//每个牛顿迭代之前先把P、Q、P_Jacobian、Q_Jacobian、C矩阵清零
	processP();
	processQ();
	processC();
    processGroundedNodeEqu();//接地点对矩阵的影响
	F_x0 = (A * (x_Newton + x) / 2 + (P + P_last) / 2) * dt_ + (B + (C + C_last) / 2) * (x_Newton - x) + (Q - Q_last) - E_Integral;
	Jacobian = (A + P_Jacobian) / 2 * dt_ + B + C / 2 + Q_Jacobian;
}
