#include "Solver_EulerBackward.h"
Solver_EulerBackward::Solver_EulerBackward(Circuit* MyCircuit) {
    size = MyCircuit->matrixDimension;
    /*---------------------矩阵初始化---------------------*/
    A = Eigen::MatrixXd::Zero(size, size);
    B = Eigen::MatrixXd::Zero(size, size);
    P_Jacobian = Eigen::MatrixXd::Zero(size, size);
    Q_Jacobian = Eigen::MatrixXd::Zero(size, size);
//    Jacobian = Eigen::MatrixXd::Zero(size, size);

    E = Eigen::VectorXd::Zero(size);
    P = Eigen::VectorXd::Zero(size);
    Q = Eigen::VectorXd::Zero(size);
    Q_last = Eigen::VectorXd::Zero(size);
//    F = Eigen::VectorXd::Zero(size);

    x = Eigen::VectorXd::Zero(size);
    /*--------------------------------------------------*/
    /*-----x的初值-----*/
    //x(0) = 0;
    //x(1) = 20;//19.4736
    //x(2) = 0;
    //x(3) = 0;//-1.94736
    for (int i = 0; i < size; i++) {
        x(i) = 0;
    }
    std::ofstream out_circuit_vars("../spice0/CircuitVarsData/CircuitVars.txt", std::ios::trunc | std::ios::out);
    out_circuit_vars.close();
    saveCircuitVars();
}

void Solver_EulerBackward::processExcitationDeivceMatrix(Circuit* MyCircuit,double t) {
    for (int m = 0; m < MyCircuit->vecExcitationDevice.size(); m++) {
        int xCountTemp = MyCircuit->vecExcitationDeviceInfo[m]->getXCount();
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);;
        Eigen::VectorXd subE = Eigen::VectorXd::Zero(xCountTemp);
        MyCircuit->vecExcitationDevice[m]->getExcitationSubMatrix(subA, subE, t);
        for (int i = 0; i < xCountTemp; i++) {
            E(*(MyCircuit->vecExcitationDeviceInfo[m]->getxIndex() + i)) += subE(i);
            for (int j = 0; j < xCountTemp; j++) {
                A(*(MyCircuit->vecExcitationDeviceInfo[m]->getxIndex() + i), *(MyCircuit->vecExcitationDeviceInfo[m]->getxIndex() + j)) += subA(i, j);
            }
        }
    }
}

void Solver_EulerBackward::processGroundedNodeEqu() {
    A.row(0).setZero();
    A(0, 0) = 1;
    B.row(0).setZero();
    P_Jacobian.row(0).setZero();
    Q_Jacobian.row(0).setZero();

    E.row(0).setZero();
    P.row(0).setZero();
    Q.row(0).setZero();
    Q_last.row(0).setZero();
}

void Solver_EulerBackward::processSetZero() {
    A.setZero();
    B.setZero();
    P_Jacobian.setZero();
    Q_Jacobian.setZero();
    E.setZero();
    P.setZero();
    Q.setZero();
    Q_last.setZero();
}

void Solver_EulerBackward::processJacobianAndF(Configuration* MyConfig, Circuit* MyCircuit, const Eigen::VectorXd x_pr, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double t1, double t2) {
    processSetZero();//每个牛顿迭代之前先把矩阵清零
    processTimeInvariantDeviceMatrix(MyCircuit);//TimeInvariantDevice其实只用填一次
    processExcitationDeivceMatrix(MyCircuit,t2);//ExcitationDeivce其实只用在每个时步填
    processTimeVariantDeviceMatrix(MyCircuit, x_pr);

    processGroundedNodeEqu();//接地点对矩阵的影响
    cout << " A = " << endl << A << endl << " B = " << endl << B << endl << " P = " << endl << P << endl << " Q = " << endl << Q << endl << " E = " << endl << E << endl;
    F = A * x_pr + B * (x_pr - x) / MyConfig->Get_dt() + P + (Q - Q_last) / MyConfig->Get_dt() - E;
    Jacobian = A + B / MyConfig->Get_dt() + P_Jacobian + Q_Jacobian / MyConfig->Get_dt();
    cout << "Jacobian" << Jacobian << endl;
    cout << "F " << F << endl;
    cout << endl;
}

void Solver_EulerBackward::solve(Configuration* MyConfig, Circuit* MyCircuit, BaseNewton* MyNewton) {
    Eigen::VectorXd x_Newton = x;
    for (int i = 0; i < MyConfig->Get_t_end() / MyConfig->Get_dt(); i++) {
        MyNewton->Perform_BaseNewton(MyConfig, MyCircuit, this, x_Newton, i * MyConfig->Get_dt(), (i + 1) * MyConfig->Get_dt());
        x = x_Newton;
        Q_last = Q;
        /*-----------------------------------*/
        saveCircuitVars();
    }
}

Solver_EulerBackward::~Solver_EulerBackward() {

}