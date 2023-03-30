#include "Solver_TR.h"
Solver_TR::Solver_TR(Circuit*  MyCircuit) {
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
    std::ofstream out_circuit_vars("../spice0/CircuitVarsData/CircuitVars.txt", std::ios::trunc | std::ios::out);
    out_circuit_vars.close();
    saveCircuitVars();
}
Solver_TR::~Solver_TR() {

}

void Solver_TR::processExcitationDeivceMatrix(Circuit* MyCircuit,double t1, double t2) {
    for (int m = 0; m < MyCircuit->vecExcitationDevice.size(); m++) {
        int xCountTemp = MyCircuit->vecExcitationDeviceInfo[m]->getXCount();
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);;
        Eigen::VectorXd subEIntegral = Eigen::VectorXd::Zero(xCountTemp);
        MyCircuit->vecExcitationDevice[m]->getExcitationIntegralSubMatrix(subA, subEIntegral, t1, t2);
        for (int i = 0; i < xCountTemp; i++) {
            E_integral(*(MyCircuit->vecExcitationDeviceInfo[m]->getxIndex() + i)) += subEIntegral(i);
            for (int j = 0; j < xCountTemp; j++) {
                A(*(MyCircuit->vecExcitationDeviceInfo[m]->getxIndex() + i), *(MyCircuit->vecExcitationDeviceInfo[m]->getxIndex() + j)) += subA(i, j);
            }
        }
    }
}

void Solver_TR::processGroundedNodeEqu() {
    A.row(0).setZero();
    A(0, 0) = 1;
    B.row(0).setZero();
    P_Jacobian.row(0).setZero();
    Q_Jacobian.row(0).setZero();

    E_integral.row(0).setZero();
    P.row(0).setZero();
    P_last.row(0).setZero();
    Q.row(0).setZero();
    Q_last.row(0).setZero();
}

void Solver_TR::processSetZero() {
    A.setZero();
    B.setZero();
    P_Jacobian.setZero();
    Q_Jacobian.setZero();
    E_integral.setZero();
    P.setZero();
    P_last.row(0).setZero();
    Q.setZero();
    Q_last.setZero();
}

void Solver_TR::processJacobianAndF(Configuration* MyConfig, Circuit* MyCircuit, const Eigen::VectorXd x_pr, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double t1, double t2) {
    processSetZero();//每个牛顿迭代之前先把矩阵清零
    processTimeInvariantDeviceMatrix(MyCircuit);//TimeInvariantDevice其实只用填一次
    processExcitationDeivceMatrix(MyCircuit,t1,t2);//ExcitationDeivce其实只用在每个时步填
    processTimeVariantDeviceMatrix(MyCircuit, x_pr);

    processGroundedNodeEqu();//接地点对矩阵的影响
    cout << " A = " << endl << A << endl << " B = " << endl << B << endl << " P = " << endl << P << endl << " Q = " << endl << Q << endl << " E_integral = " << endl << E_integral << endl;
    cout << " P_Jacobian = " << endl << P_Jacobian << endl << " Q_Jacobian = " << Q_Jacobian << endl;
    F = ((t2 - t1) / 2 * A + B) * x_pr + (t2 - t1) / 2 * P + Q - (-(t2 - t1) / 2 * A + B) * x - (-(t2 - t1) / 2 * P_last + Q_last) - E_integral;
    Jacobian = (t2 - t1) / 2 * A + B + (t2 - t1) / 2 * P_Jacobian + Q_Jacobian;
    cout << "Jacobian = " << endl << Jacobian << endl;
    cout << "F  = " << endl << F << endl;
    cout << endl;
}

void Solver_TR::solve(Configuration* MyConfig, Circuit* MyCircuit, BaseNewton* MyNewton) {
    Eigen::VectorXd x_Newton = x;
    for (int i = 0; i < MyConfig->Get_t_end() / MyConfig->Get_dt(); i++) {
        MyNewton->Perform_BaseNewton(MyConfig, MyCircuit, this, x_Newton, i * MyConfig->Get_dt(), (i + 1) * MyConfig->Get_dt());
        x = x_Newton;
        Q_last = Q;
        P_last = P;
        /*-----------------------------------*/
        saveCircuitVars();
    }
}