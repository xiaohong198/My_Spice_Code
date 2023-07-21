#include "SolverBDF2.h"
SolverBDF2::SolverBDF2(Configuration* _my_config, Circuit* _my_circuit) :Solver(_my_config, _my_circuit) {
	a0_ = 1.5;
	a1_ = -2;
	a2_ = 0.5;
}

SolverBDF2::~SolverBDF2() {
}

void SolverBDF2::GetCoff() {
	a0_ = 1.5;
	a1_ = -2;
	a2_ = 0.5;
}

void SolverBDF2::ProcessJacobianAndF() {
	ProcessSetZero();//ÿ��ţ�ٵ���֮ǰ�Ȱ�P��Q��P_Jacobian��Q_Jacobian��C��������
	ProcessP();
	ProcessQ();
	ProcessC();
	ProcessGroundedNodeEqu();//�ӵص�Ծ����Ӱ��
	void getCoff();//ʱ�䲽�仯ʱ����
	F_x0_ = (A_ * x_newton_ + P_) * dt_ + B_ * (a0_ * x_newton_ + a1_ * x_ + a2_ * x_s2_) + (a0_ * Q_ + a1_ * Q_s1_ + a2_ * Q_s2_) + (C_ * a0_ * x_newton_ + C_s1_ * a1_ * x_ + C_s2_ * a2_ * x_s2_) - E_Integral_;
	Jacobian_ = (A_ + P_Jacobian_) * dt_ + B_ * a0_ + a0_ * Q_Jacobian_ + a0_ * C_;

	Eigen::VectorXd F_BE = (A_ * x_newton_ + P_) * dt_ + (B_ + C_) * (x_newton_ - x_) + (Q_ - Q_s1_) - E_Integral_;
	//	cout << "F_BE = " << endl << F_BE << endl;
}