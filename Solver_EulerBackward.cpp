#include "Solver_EulerBackward.h"
Solver_EulerBackward::Solver_EulerBackward(Configuration* MyConfig, Circuit* MyCircuit):Solver(MyConfig, MyCircuit) 
{
}
Solver_EulerBackward::~Solver_EulerBackward() 
{
}

void Solver_EulerBackward::processJacobianAndF(const Eigen::VectorXd x_pr, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, int index) {
	processSetZero();//ÿ��ţ�ٵ���֮ǰ�ȰѾ�������
	Solver::processTimeVariantDeviceMatrix(MyCircuit_, x_pr);
	processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��

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
		A = A_mid;	B = B_mid;	E = E_mid;

		processExcitationDeivceMatrix(i);//ExcitationDeivce��ʵֻ����ÿ��ʱ����

		MyNewton->Perform_BaseNewton(x_Newton, i);
		x = x_Newton;

        Q_last = Q;
        /*-----------------------------------*/
        //saveCircuitVars();
		Solver::x_result_vec_.push_back(Solver::x);
    }
}
