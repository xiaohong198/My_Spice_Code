#include "Solver_TR.h"
Solver_TR::Solver_TR(Configuration* MyConfig, Circuit* MyCircuit) :Solver(MyConfig, MyCircuit) {
}
Solver_TR::~Solver_TR() {

}

void Solver_TR::processJacobianAndF() {
    processSetZero();//ÿ��ţ�ٵ���֮ǰ�Ȱ�P��Q��P_Jacobian��Q_Jacobian��C��������
	processP();
	processQ();
	processC();
    processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��
	F_x0 = (A * (x_Newton + x) / 2 + (P + P_last) / 2) * dt_ + (B + (C + C_last) / 2) * (x_Newton - x) + (Q - Q_last) - E_Integral;
	Jacobian = (A + P_Jacobian) / 2 * dt_ + B + C / 2 + Q_Jacobian;
}
