#include "Solver_TR.h"
Solver_TR::Solver_TR(Configuration* MyConfig, Circuit* MyCircuit) :Solver(MyConfig, MyCircuit) {
    size = MyCircuit->matrixDimension;
    /*---------------------矩阵初始化---------------------*/
    A = Eigen::MatrixXd::Zero(size, size);
    B = Eigen::MatrixXd::Zero(size, size);
    P_Jacobian = Eigen::MatrixXd::Zero(size, size);
    Q_Jacobian = Eigen::MatrixXd::Zero(size, size);
    //    Jacobian = Eigen::MatrixXd::Zero(size, size);

    E_integral = Eigen::VectorXd::Zero(size);
    P = Eigen::VectorXd::Zero(size);
    P_last = Eigen::VectorXd::Zero(size);
    Q = Eigen::VectorXd::Zero(size);
    Q_last = Eigen::VectorXd::Zero(size);
    //    F = Eigen::VectorXd::Zero(size);

    x = Eigen::VectorXd::Zero(size);
    /*--------------------------------------------------*/
    /*-----x的初值-----*/
    //x(0) = 0;
    //x(1) = 0;//19.4736
    //x(2) = 20;
    //x(3) = 0;//-1.94736
    for (int i = 0; i < size; i++) {
        x(i) = 0;
    }
    x(1) = 20;
    std::ofstream out_circuit_vars("../spice0/CircuitVarsData/CircuitVars.txt", std::ios::trunc | std::ios::out);
    out_circuit_vars.close();
    saveCircuitVars();
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
    processSetZero();//每个牛顿迭代之前先把P、Q、P_Jacobian、Q_Jacobian、C矩阵清零
    processPandQandC();
    processGroundedNodeEqu();//接地点对矩阵的影响
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