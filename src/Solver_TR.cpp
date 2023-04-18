#include "Solver_TR.h"
Solver_TR::Solver_TR(Configuration* MyConfig,Circuit*  MyCircuit):Solver(MyConfig, MyCircuit) 
{
}
Solver_TR::~Solver_TR() 
{
}

void Solver_TR::processJacobianAndF() {
	Solver::processSetZero();//ÿ��ţ�ٵ���֮ǰ�ȰѾ�������
	Solver::processSetZeroABE();
	Solver::processTimeInvariantDeviceMatrix();//TimeInvariantDevice��ʵֻ����һ��
	Solver::processExcitationDeivceMatrix(index);//ExcitationDeivce��ʵֻ����ÿ��ʱ����
	Solver::processTimeVariantDeviceMatrix();
	Solver::processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��

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