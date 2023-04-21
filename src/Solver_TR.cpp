#include "Solver_TR.h"
Solver_TR::Solver_TR(Configuration* MyConfig, Circuit* MyCircuit) :Solver(MyConfig, MyCircuit) {
}
Solver_TR::~Solver_TR() {

}

//void Solver_TR::processEIntegral(Circuit* MyCircuit,double* tList) {
//    for (int m = 0; m < MyCircuit->vecExcitationDevice.size(); m++) {
//        int xCountTemp = MyCircuit->vecExcitationDeviceInfo[m]->getXCount();
//        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);;
//        Eigen::VectorXd subEIntegral = Eigen::VectorXd::Zero(xCountTemp);
//        MyCircuit->vecExcitationDevice[m]->getExcitationIntegralSubMatrix(subA, subEIntegral, t1, t2);
//        for (int i = 0; i < xCountTemp; i++) {
//            E_integral(*(MyCircuit->vecExcitationDeviceInfo[m]->getxIndex() + i)) += subEIntegral(i);
//            for (int j = 0; j < xCountTemp; j++) {
//                A(*(MyCircuit->vecExcitationDeviceInfo[m]->getxIndex() + i), *(MyCircuit->vecExcitationDeviceInfo[m]->getxIndex() + j)) += subA(i, j);
//            }
//        }
//    }
//}

//void Solver_TR::processGroundedNodeEqu() {
//    A.row(0).setZero();
//    A(0, 0) = 1;
//    B.row(0).setZero();
//    P_Jacobian.row(0).setZero();
//    Q_Jacobian.row(0).setZero();
//
//    E_integral.row(0).setZero();
//    P.row(0).setZero();
//    P_last.row(0).setZero();
//    Q.row(0).setZero();
//    Q_last.row(0).setZero();
//}
//
//void Solver_TR::processSetZero() {
//    A.setZero();
//    B.setZero();
//    P_Jacobian.setZero();
//    Q_Jacobian.setZero();
//    E_integral.setZero();
//    P.setZero();
//    P_last.row(0).setZero();
//    Q.setZero();
//    Q_last.setZero();
//}

void Solver_TR::processJacobianAndF() {
    processSetZero();//ÿ��ţ�ٵ���֮ǰ�Ȱ�P��Q��P_Jacobian��Q_Jacobian��C��������
    processPandQandC();
    processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��
	F_x0 = (A * x_Newton + P) * dt_ + (B + C) * (x_Newton - x) + (Q - Q_last) - E_Integral;
    Jacobian = (A + P_Jacobian) * dt_ + B + C + Q_Jacobian;
}

//void Solver_TR::solve(Configuration* MyConfig, Circuit* MyCircuit, BaseNewton* MyNewton) {
//    Eigen::VectorXd x_Newton = x;
//    int N = MyConfig->Get_t_end() / MyConfig->Get_dt();
//    for (int i = 0; i < N; i++) {
//        MyNewton->Perform_BaseNewton(MyConfig, MyCircuit, this, x_Newton, i * MyConfig->Get_dt(), (i + 1) * MyConfig->Get_dt());
//        x = x_Newton;
//        Q_last = Q;
//        P_last = P;
//        /*-----------------------------------*/
//        saveCircuitVars();
//    }
//}