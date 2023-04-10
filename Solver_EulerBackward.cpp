#include "Solver_EulerBackward.h"
Solver_EulerBackward::Solver_EulerBackward(Configuration* MyConfig, Circuit* MyCircuit) {
	MyConfig_ = MyConfig;
	MyCircuit_ = MyCircuit;
    size = MyCircuit_->matrixDimension;
    /*---------------------矩阵初始化---------------------*/
    A = Eigen::MatrixXd::Zero(size, size);
    B = Eigen::MatrixXd::Zero(size, size);
    P_Jacobian = Eigen::MatrixXd::Zero(size, size);
    Q_Jacobian = Eigen::MatrixXd::Zero(size, size);
//    Jacobian = Eigen::MatrixXd::Zero(size, size)
	;

    E = Eigen::VectorXd::Zero(size);
    P = Eigen::VectorXd::Zero(size);
    Q = Eigen::VectorXd::Zero(size);
    Q_last = Eigen::VectorXd::Zero(size);
//    F = Eigen::VectorXd::Zero(size);

    x = Eigen::VectorXd::Zero(size);
	//Jacobian = Eigen::MatrixXd::Zero(size, size);
	//F_x0 = Eigen::VectorXd::Zero(size);

	dt_ = MyConfig_->Get_dt();
	t_end_ = MyConfig_->Get_t_end();

    /*--------------------------------------------------*/
    /*-----x的初值-----*/
    //x(0) = 0;
    //x(1) = 20;//19.4736
    //x(2) = 0;
    //x(3) = 0;//-1.94736
    for (int i = 0; i < size; i++) {
        x(i) = 0;
    }
	Solver::x_result_vec_.push_back(Solver::x);

	processSetZero();//每个牛顿迭代之前先把矩阵清零
	Solver::processTimeInvariantDeviceMatrix(MyCircuit_);//TimeInvariantDevice其实只用填一次


}

void Solver_EulerBackward::processExcitationDeivceMatrix(double t) {
    for (int m = 0; m < MyCircuit_->vecExcitationDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit_->vecExcitationDeviceInfo[m];
		vector<int> index = current_info.xIndex;
        int xCountTemp = current_info.xCount;
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::VectorXd subE = Eigen::VectorXd::Zero(xCountTemp);
		MyCircuit_->vecExcitationDevice[m]->getExcitationSubMatrix(subA, subE, t);
        for (int i = 0; i < xCountTemp; i++) {
            E(index[i]) += subE(i);
            for (int j = 0; j < xCountTemp; j++) {
                A(index[i], index[j]) += subA(i, j);
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

void Solver_EulerBackward::processJacobianAndF(const Eigen::VectorXd x_pr, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, double t1, double t2) {


    //cout << " A = " << endl << A << endl << " B = " << endl << B << endl << " P = " << endl << P << endl << " Q = " << endl << Q << endl << " E = " << endl << E << endl;
    F = A * x_pr + B * (x_pr - x) / dt_ + P + (Q - Q_last) / dt_ - E;
    Jacobian = A + B / dt_ + P_Jacobian + Q_Jacobian / dt_;
    //cout << "Jacobian" << Jacobian << endl;
    //cout << "F " << F << endl;
    //cout << endl;
}

void Solver_EulerBackward::solve(BaseNewton* MyNewton) {
    Eigen::VectorXd x_Newton = x;
    for (int i = 0; i < t_end_ / dt_; i++) {

		MyNewton->Perform_BaseNewton(x_Newton, i * dt_, (i + 1) * dt_);
		x = x_Newton;
		processExcitationDeivceMatrix((i + 1) * dt_);//ExcitationDeivce其实只用在每个时步填
		Solver::processTimeVariantDeviceMatrix(MyCircuit_, x_Newton);
		processGroundedNodeEqu();//接地点对矩阵的影响

        Q_last = Q;
        /*-----------------------------------*/
        //saveCircuitVars();
		Solver::x_result_vec_.push_back(Solver::x);
    }
}

void Solver_EulerBackward::Perform_BaseNewton_solver(Eigen::VectorXd& x_Newton, double t1, double t2)
{
	//int Max_Iteration_times = 1000;
	//double Convergence_limit = 0.0001;

	//for (int Iteration_times = 0; Iteration_times < Max_Iteration_times; Iteration_times++)
	//{
	//	processJacobianAndF(x_Newton, Jacobian, F_x0, t1, t2);
	//	x_Newton = x_Newton - Jacobian.inverse() * F_x0;
	//	//cout << "Every Iteration x_Newton = " << endl << x_Newton << endl;
	//	if (((F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false)) {
	//		//cout << "Convergent Already! F_x0 = " << endl << F_x0 << endl;
	//		break;
	//	}
	//}
}

Solver_EulerBackward::~Solver_EulerBackward() {

}