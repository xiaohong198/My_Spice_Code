#include "Solver_BDF2.h"
Solver_BDF2::Solver_BDF2(Configuration* MyConfig, Circuit* MyCircuit) :Solver(MyConfig, MyCircuit) {
	a0 = 1.5;
	a1 = -2;
	a2 = 0.5;
}

Solver_BDF2::~Solver_BDF2() {
}

void Solver_BDF2::getCoff() {
	a0 = 1.5;
	a1 = -2;
	a2 = 0.5;
}

void Solver_BDF2::processJacobianAndF() {
	processSetZero();//ÿ��ţ�ٵ���֮ǰ�Ȱ�P��Q��P_Jacobian��Q_Jacobian��C��������
	processP();
	processQ();
	processC();
	processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��
	void getCoff();//ʱ�䲽�仯ʱ����
	F_x0 = (A * x_Newton + P) * dt_ + B * (a0 * x_Newton + a1 * x + a2 * x_s2) + (a0 * Q + a1 * Q_s1 + a2 * Q_s2) + (C * a0 * x_Newton + C_s1 * a1 * x + C_s2 * a2 * x_s2) - E_Integral;
	Jacobian = (A + P_Jacobian) * dt_ + B * a0 + a0 * Q_Jacobian + a0 * C;

	Eigen::VectorXd F_BE = (A * x_Newton + P) * dt_ + (B + C) * (x_Newton - x) + (Q - Q_s1) - E_Integral;
	//	cout << "F_BE = " << endl << F_BE << endl;
}