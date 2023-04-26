#include "Solver_TR.h"
Solver_TR::Solver_TR(Configuration* MyConfig, Circuit* MyCircuit) :Solver(MyConfig, MyCircuit) {
}
Solver_TR::~Solver_TR() {

}

void Solver_TR::processJacobianAndF() {
    processSetZero();//ÿ��ţ�ٵ���֮ǰ�Ȱ�P��Q��P_Jacobian��Q_Jacobian��C��������
    processPandQandC();
    processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��
	F_x0 = (A * x_Newton + P) * dt_ + (B + C) * (x_Newton - x) + (Q - Q_last) - E_Integral;
    Jacobian = (A + P_Jacobian) * dt_ + B + C + Q_Jacobian;
}
