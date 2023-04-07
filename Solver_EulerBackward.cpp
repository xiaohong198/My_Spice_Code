#include "Solver_EulerBackward.h"
Solver_EulerBackward::Solver_EulerBackward(Configuration* MyConfig,Circuit* MyCircuit) {
	Solver::MyConfig_ = MyConfig;
	Solver::MyCircuit_ = MyCircuit;
    Solver::size = MyCircuit_->matrixDimension;
    /*---------------------矩阵初始化---------------------*/
	Solver::A = Eigen::MatrixXd::Zero(size, size);
	Solver::B = Eigen::MatrixXd::Zero(size, size);
	Solver::P_Jacobian = Eigen::MatrixXd::Zero(size, size);
	Solver::Q_Jacobian = Eigen::MatrixXd::Zero(size, size);
//    Jacobian = Eigen::MatrixXd::Zero(size, size);

    E = Eigen::VectorXd::Zero(size);
	Solver::P = Eigen::VectorXd::Zero(size);
	Solver::Q = Eigen::VectorXd::Zero(size);
	Solver::Q_last = Eigen::VectorXd::Zero(size);
//    F = Eigen::VectorXd::Zero(size);

	Solver::x = Eigen::VectorXd::Zero(size);
	Jacobian = Eigen::MatrixXd::Zero(size, size);
	F_x0 = Eigen::VectorXd::Zero(size);
	x_Newton = Eigen::VectorXd::Zero(size);
	dt_ = MyConfig_->Get_dt();
	t_end_ = MyConfig_->Get_t_end();

    /*--------------------------------------------------*/
    /*-----x的初值-----*/
    //x(0) = 0;
    //x(1) = 20;//19.4736
    //x(2) = 0;
    //x(3) = 0;//-1.94736
    for (int i = 0; i < Solver::size; i++) {
		Solver::x(i) = 0;
    }
	Solver::x_result_vec_.push_back(Solver::x);

    //std::ofstream out_circuit_vars("../spice0/CircuitVarsData/CircuitVars.txt", std::ios::trunc | std::ios::out);
    //out_circuit_vars.close();
    //Solver::saveCircuitVars();
}
#include <chrono>
//07-EulerBackward
void Solver_EulerBackward::processExcitationDeivceMatrix(double t) {
	//auto start = std::chrono::steady_clock::now();
	//循环-04
	for (int m = 0; m < MyCircuit_->vecExcitationDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit_->vecExcitationDeviceInfo[m];
		vector<int> index = current_info.xIndex;
        int xCountTemp = current_info.xCount;
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);;
        Eigen::VectorXd subE = Eigen::VectorXd::Zero(xCountTemp);
		MyCircuit_->vecExcitationDevice[m]->getExcitationSubMatrix(subA, subE, t);
        for (int i = 0; i < xCountTemp; i++) {
            E(index[i]) += subE(i);
            for (int j = 0; j < xCountTemp; j++) {
                A(index[i], index[j]) += subA(i, j);
            }
        }
    }
	//auto end = std::chrono::steady_clock::now();

	//auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//cout << "processExcitationDeivceMatrix程序用时:" << time.count() / 1000 << "毫秒" << endl;


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
//05-EulerBackward
void Solver_EulerBackward::processJacobianAndF(double t1,double t2) {
    processSetZero();//每个牛顿迭代之前先把矩阵清零
	//06-EulerBackward
	//循环-03
	Solver::processTimeInvariantDeviceMatrix();//TimeInvariantDevice其实只用填一次
    //07-EulerBackward
	//循环-04
	processExcitationDeivceMatrix(t2);//ExcitationDeivce其实只用在每个时步填
    //08-EulerBackward
	//循环-05
	Solver::processTimeVariantDeviceMatrix( x_Newton);

    processGroundedNodeEqu();//接地点对矩阵的影响
    //cout << " A = " << endl << A << endl << " B = " << endl << B << endl << " P = " << endl << P << endl << " Q = " << endl << Q << endl << " E = " << endl << E << endl;
	F_x0 = A * x_Newton + B * (x_Newton - x) / dt_ + P + (Q - Q_last) / dt_ - E;
    Jacobian = A + B / dt_ + P_Jacobian + Q_Jacobian / dt_;
    //cout << "Jacobian" << Jacobian << endl;
    //cout << "F " << F << endl;
    //cout << endl;
}
#include <chrono>
//03-EulerBackward
void Solver_EulerBackward::solve(BaseNewton* MyNewton) {

	MyNewton_ = MyNewton;
	//auto start = std::chrono::steady_clock::now();

	//循环-01
    for (int i = 0; i < t_end_ / dt_; i++)
	{
		//04-09-EulerBackward
		//循环-02-05
		Perform_BaseNewton_solver(i * dt_,(i + 1) * dt_);
        //MyNewton->Perform_BaseNewton(MyConfig, MyCircuit, this, x_Newton, i * dt_, (i + 1) * dt_);
		//重新赋值
		Solver::x = x_Newton;
        Q_last = Q;
        /*-----------------------------------*/
		//10-EulerBackward
		//循环-06
		//Solver::saveCircuitVars();

		Solver::x_result_vec_.push_back(Solver::x);
    }
	//auto end = std::chrono::steady_clock::now();

	//auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//cout << "solve程序用时:" << time.count() / 1000 << "毫秒" << endl;

}

void Solver_EulerBackward::Perform_BaseNewton_solver(double t1,double t2)
{
	int Max_Iteration_times = 1000;
	double Convergence_limit = 0.0001;
	int Iteration_times = 0;

	for (int Iteration_times = 0; Iteration_times < Max_Iteration_times; Iteration_times++)
	{
		//05-08-EulerBackward-Trapezoidal
		//循环-03-05
		processJacobianAndF(t1, t2);
		x_Newton = x_Newton - Jacobian.inverse() * F_x0;
		//cout << "Every Iteration x_Newton = " << endl << x_Newton << endl;
		//09-EulerBackward-Trapezoidal
		if (((F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false)) {
			//cout << "Convergent Already! F_x0 = " << endl << F_x0 << endl;
			break;
		}
	}
	//while (Iteration_times < Max_Iteration_times) {
	//	//05-08-EulerBackward-Trapezoidal
	//	//循环-03-05
	//	processJacobianAndF(t1,t2);
	//	x_Newton = x_Newton - Jacobian.inverse() * F_x0;
	//	//cout << "Every Iteration x_Newton = " << endl << x_Newton << endl;
	//	Iteration_times++;
	//	//09-EulerBackward-Trapezoidal
	//	if (((F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false)) {
	//		//cout << "Convergent Already! F_x0 = " << endl << F_x0 << endl;
	//		break;
	//	}
	//}
}

Solver_EulerBackward::~Solver_EulerBackward() {
	delete MyNewton_;
	MyNewton_ = nullptr;
}