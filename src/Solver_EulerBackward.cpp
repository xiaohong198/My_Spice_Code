#include "Solver_EulerBackward.h"
Solver_EulerBackward::Solver_EulerBackward(Configuration* MyConfig, Circuit* MyCircuit) :Solver(MyConfig, MyCircuit) {
}

//void Solver_EulerBackward::processGroundedNodeEqu() {
//    A.row(0).setZero();
//    A(0, 0) = 1;
//    B.row(0).setZero();
//    P_Jacobian.row(0).setZero();
//    Q_Jacobian.row(0).setZero();
//
//    E.row(0).setZero();
//    P.row(0).setZero();
//    Q.row(0).setZero();
//    Q_last.row(0).setZero();
//}

//void Solver_EulerBackward::processSetZero() {
//    A.setZero();
//    B.setZero();
//    P_Jacobian.setZero();
//    Q_Jacobian.setZero();
//    E.setZero();
//    P.setZero();
//    Q.setZero();
//    Q_last.setZero();
//}

void Solver_EulerBackward::processJacobianAndF() {
    processSetZero();//ÿ��ţ�ٵ���֮ǰ�Ȱ�P��Q��P_Jacobian��Q_Jacobian��C��������
    processPandQandC();
    processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��
	F_x0 = (A * x_Newton + P) * dt_ + (B + C) * (x_Newton - x) + (Q - Q_last) - E_Integral;
    Jacobian = (A + P_Jacobian) * dt_ + B + C + Q_Jacobian;
}

//void Solver_EulerBackward::solve(Configuration* MyConfig, Circuit* MyCircuit, BaseNewton* MyNewton) {
//    Eigen::VectorXd x_Newton = x;//��ʼ��
//    int N = MyConfig->Get_t_end() / MyConfig->Get_dt();
//    processAandB(MyCircuit);//A��Bֻ��һ�ξͲ�����
//    for (int i = 0; i < N; i++) {
//        double tList[2] = { i * MyConfig->Get_dt(),(i + 1) * MyConfig->Get_dt() };
//        processEIntegral(MyCircuit, tList);
//        MyNewton->Perform_BaseNewton(MyConfig, MyCircuit, this, x_Newton, tList);
//        x = x_Newton;
//        Q_last = Q;
//        saveCircuitVars();
//    }
//}

Solver_EulerBackward::~Solver_EulerBackward() {

}