#include "Solver_EulerBackward.h"
Solver_EulerBackward::Solver_EulerBackward(Configuration* MyConfig, Circuit* MyCircuit):Solver(MyConfig, MyCircuit) 
{
}
Solver_EulerBackward::~Solver_EulerBackward() 
{
}

void Solver_EulerBackward::processJacobianAndF() {
	Solver::processSetZero();//每个牛顿迭代之前先把矩阵清零
	Solver::processTimeVariantDeviceMatrix();
	Solver::processGroundedNodeEqu();//接地点对矩阵的影响

	F_x0 = A * x_Newton + B * (x_Newton - x) / dt_ + P + (Q - Q_last) / dt_ - E;
    Jacobian = A + B / dt_ + P_Jacobian + Q_Jacobian / dt_;
}

void Solver_EulerBackward::solve() {
    for (index = 0; index < t_end_ / dt_; index++) {
		A = A_mid;	B = B_mid;	E = E_mid;
		processExcitationDeivceMatrix(index);//ExcitationDeivce其实只用在每个时步填

		MyNewton->Perform_BaseNewton();

        Q_last = Q;
		Solver::x_result_vec_.push_back(Solver::x_Newton);
    }
}

void Solver_EulerBackward::processExcitationDeivceMatrix(int _index) {
	double t1 = _index * dt_;
	double t2 = (_index + 1) * dt_;
	for (int m = 0; m < MyCircuit_->vecExcitationDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit_->vecExcitationDeviceInfo[m];
		vector<int> index = current_info.xIndex;
		int xCountTemp = current_info.xCount;

		Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);;
		Eigen::VectorXd subE = Eigen::VectorXd::Zero(xCountTemp);

		string child_name = typeid(*this).name();
		
		MyCircuit_->vecExcitationDevice[m]->getExcitationSubMatrix(subA, subE, t2);

		for (int i = 0; i < xCountTemp; i++) {
			E(index[i]) += subE(i);
			for (int j = 0; j < xCountTemp; j++) {
				A(index[i], index[j]) += subA(i, j);
			}
		}
	}
}

