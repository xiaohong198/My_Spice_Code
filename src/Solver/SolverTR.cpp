#include "SolverTR.h"
SolverTR::SolverTR(Configuration* _my_config, Circuit* _my_circuit) :Solver(_my_config, _my_circuit) {
}
SolverTR::~SolverTR() {
}

void SolverTR::ProcessJacobianAndF() {
	ProcessSetZero();//每个牛顿迭代之前先把P、Q、P_Jacobian、Q_Jacobian、C矩阵清零
	ProcessP();
	ProcessQ();
	ProcessC();
	ProcessGroundedNodeEqu();//接地点对矩阵的影响
	F_x0_ = (A_ * (x_newton_ + x_) / 2 + (P_ + P_s1_) / 2) * dt_ + (B_ + (C_ + C_s1_) / 2) * (x_newton_ - x_) + (Q_ - Q_s1_) - E_Integral_;
	Jacobian_ = (A_ + P_Jacobian_) / 2 * dt_ + B_ + C_ / 2 + Q_Jacobian_;
}