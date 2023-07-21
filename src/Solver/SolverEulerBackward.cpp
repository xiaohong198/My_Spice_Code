#include "SolverEulerBackward.h"
SolverEulerBackward::SolverEulerBackward(Configuration* _my_config, Circuit* _my_circuit) :Solver(_my_config, _my_circuit) {
}
void SolverEulerBackward::ProcessJacobianAndF() {
	ProcessSetZero();//每个牛顿迭代之前先把P、Q、P_Jacobian、Q_Jacobian、C矩阵清零
	ProcessP();
	ProcessQ();
	ProcessC();
	ProcessGroundedNodeEqu();//�ӵص�Ծ����Ӱ��
	F_x0_ = (A_ * x_newton_ + P_) * dt_ + (B_ + C_) * (x_newton_ - x_) + (Q_ - Q_s1_) - E_Integral_;
	Jacobian_ = (A_ + P_Jacobian_) * dt_ + B_ + C_ + Q_Jacobian_;
}

SolverEulerBackward::~SolverEulerBackward() {
}