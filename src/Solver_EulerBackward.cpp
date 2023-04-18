#include "Solver_EulerBackward.h"
Solver_EulerBackward::Solver_EulerBackward(Configuration* MyConfig, Circuit* MyCircuit):Solver(MyConfig, MyCircuit) 
{
}
Solver_EulerBackward::~Solver_EulerBackward() 
{
}

void Solver_EulerBackward::processJacobianAndF() {
	Solver::processSetZero();//ÿ��ţ�ٵ���֮ǰ�ȰѾ�������
	Solver::processTimeVariantDeviceMatrix();
	Solver::processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��

	F_x0 = A * x_Newton + B * (x_Newton - x) / dt_ + P + (Q - Q_last) / dt_ - E;
    Jacobian = A + B / dt_ + P_Jacobian + Q_Jacobian / dt_;
}

void Solver_EulerBackward::solve() {
    for (index = 0; index < t_end_ / dt_; index++) {
		A = A_mid;	B = B_mid;	E = E_mid;
		Solver::processExcitationDeivceMatrix(index);//ExcitationDeivce��ʵֻ����ÿ��ʱ����

		MyNewton->Perform_BaseNewton();

        Q_last = Q;
		Solver::x_result_vec_.push_back(Solver::x_Newton);
    }
}
