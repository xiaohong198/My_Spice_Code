#include "Solver_TR.h"
Solver_TR::Solver_TR(Configuration* MyConfig,Circuit*  MyCircuit):Solver(MyConfig, MyCircuit) 
{
}
Solver_TR::~Solver_TR() 
{
}

void Solver_TR::processJacobianAndF() {
	Solver::processSetZero();//每个牛顿迭代之前先把矩阵清零
	Solver::processSetZeroABE();
	Solver::processTimeInvariantDeviceMatrix();//TimeInvariantDevice其实只用填一次
	processExcitationDeivceMatrix(index);//ExcitationDeivce其实只用在每个时步填
	Solver::processTimeVariantDeviceMatrix();
	Solver::processGroundedNodeEqu();//接地点对矩阵的影响

	double t1 = index * dt_;
	double t2 = (index + 1) * dt_;

	F_x0 = ((t2 - t1) / 2 * A + B) * x_Newton + (t2 - t1) / 2 * P + Q - (-(t2 - t1) / 2 * A + B) * x - (-(t2 - t1) / 2 * P_last + Q_last) - E;
    Jacobian = (t2 - t1) / 2 * A + B + (t2 - t1) / 2 * P_Jacobian + Q_Jacobian;
}

void Solver_TR::solve() {
	for (index = 0; index < t_end_ / dt_; index++) {

		MyNewton->Perform_BaseNewton();

		Q_last = Q;
		P_last = P;
		Solver::x_result_vec_.push_back(x_Newton);
	}
}

void Solver_TR::processExcitationDeivceMatrix(int _index) {
	double t1 = _index * dt_;
	double t2 = (_index + 1) * dt_;
	for (int m = 0; m < MyCircuit_->vecExcitationDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit_->vecExcitationDeviceInfo[m];
		vector<int> index = current_info.xIndex;
		int xCountTemp = current_info.xCount;

		Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);;
		Eigen::VectorXd subE = Eigen::VectorXd::Zero(xCountTemp);

		string child_name = typeid(*this).name();

		MyCircuit_->vecExcitationDevice[m]->getExcitationIntegralSubMatrix(subA, subE, t1, t2);

		for (int i = 0; i < xCountTemp; i++) {
			E(index[i]) += subE(i);
			for (int j = 0; j < xCountTemp; j++) {
				A(index[i], index[j]) += subA(i, j);
			}
		}
	}
}



