#include "Solver_TR.h"
Solver_TR::Solver_TR(Configuration* MyConfig,Circuit*  MyCircuit):Solver(MyConfig, MyCircuit) 
{
}
Solver_TR::~Solver_TR() 
{
}

void Solver_TR::processJacobianAndF(const Eigen::VectorXd x_pr, Eigen::MatrixXd& Jacobian, Eigen::VectorXd& F, int index) {
    processSetZero();//ÿ��ţ�ٵ���֮ǰ�ȰѾ�������
	processSetZeroABE();
    processTimeInvariantDeviceMatrix(MyCircuit_);//TimeInvariantDevice��ʵֻ����һ��
    processExcitationDeivceMatrix(index);//ExcitationDeivce��ʵֻ����ÿ��ʱ����
    processTimeVariantDeviceMatrix(MyCircuit_, x_pr);

    processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��

	double t1 = index * dt_;
	double t2 = (index + 1) * dt_;

    //cout << " A = " << endl << A << endl << " B = " << endl << B << endl << " P = " << endl << P << endl << " Q = " << endl << Q << endl << " E_integral = " << endl << E_integral << endl;
    //cout << " P_Jacobian = " << endl << P_Jacobian << endl << " Q_Jacobian = " << Q_Jacobian << endl;
	F = ((t2 - t1) / 2 * A + B) * x_pr + (t2 - t1) / 2 * P + Q - (-(t2 - t1) / 2 * A + B) * x - (-(t2 - t1) / 2 * P_last + Q_last) - E;
    Jacobian = (t2 - t1) / 2 * A + B + (t2 - t1) / 2 * P_Jacobian + Q_Jacobian;
    //cout << "Jacobian = " << endl << Jacobian << endl;
    //cout << "F  = " << endl << F << endl;
    //cout << endl;
}

void Solver_TR::solve(BaseNewton* MyNewton) {
    Eigen::VectorXd x_Newton = x;
    for (int i = 0; i < t_end_ / dt_; i++) {
		MyNewton->Perform_BaseNewton(x_Newton, i);
		x = x_Newton;
        Q_last = Q;
        P_last = P;
        /*-----------------------------------*/
        //saveCircuitVars();
		Solver::x_result_vec_.push_back(x);

	}
}
