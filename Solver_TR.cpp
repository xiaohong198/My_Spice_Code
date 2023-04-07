#include "Solver_TR.h"
Solver_TR::Solver_TR(Configuration* MyConfig, Circuit*  MyCircuit) {
	MyConfig_ = MyConfig;
	MyCircuit_ = MyCircuit;
    size = MyCircuit->matrixDimension;
    /*---------------------�����ʼ��---------------------*/
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
	Jacobian = Eigen::MatrixXd::Zero(size, size);
	F_x0 = Eigen::VectorXd::Zero(size);
	x_Newton = Eigen::VectorXd::Zero(size);
    /*--------------------------------------------------*/
    /*-----x�ĳ�ֵ-----*/
    //x(0) = 0;
    //x(1) = 0;//19.4736
    //x(2) = 20;
    //x(3) = 0;//-1.94736
    for (int i = 0; i < size; i++) {
        x(i) = 0;
    }
	Solver::x_result_vec_.push_back(x);

    //std::ofstream out_circuit_vars("../spice0/CircuitVarsData/CircuitVars.txt", std::ios::trunc | std::ios::out);
    //out_circuit_vars.close();
    //saveCircuitVars();
}
Solver_TR::~Solver_TR() {
	delete MyNewton_;
}
//07-Trapezoidal
void Solver_TR::processExcitationDeivceMatrix(double t1,double t2) {
    for (int m = 0; m < MyCircuit_->vecExcitationDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit_->vecExcitationDeviceInfo[m];
		vector<int> index = current_info.xIndex;
        int xCountTemp = current_info.xCount;
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);;
        Eigen::VectorXd subEIntegral = Eigen::VectorXd::Zero(xCountTemp);
        MyCircuit_->vecExcitationDevice[m]->getExcitationIntegralSubMatrix(subA, subEIntegral,t1, t2);
        for (int i = 0; i < xCountTemp; i++) {
            E_integral(index[i]) += subEIntegral(i);
            for (int j = 0; j < xCountTemp; j++) {
                A(index[i], index[j]) += subA(i, j);
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
//05-Trapezoidal
void Solver_TR::processJacobianAndF(double t1,double t2) {

	double 
    processSetZero();//ÿ��ţ�ٵ���֮ǰ�ȰѾ�������
    //06-Trapezoidal
	//ѭ��03
	Solver::processTimeInvariantDeviceMatrix();//TimeInvariantDevice��ʵֻ����һ��
    //07-Trapezoidal
	//ѭ��04
	processExcitationDeivceMatrix(t1,t2);//ExcitationDeivce��ʵֻ����ÿ��ʱ����
    //08-Trapezoidal
	//ѭ��05
	Solver::processTimeVariantDeviceMatrix(x_Newton);

    processGroundedNodeEqu();//�ӵص�Ծ����Ӱ��
    //cout << " A = " << endl << A << endl << " B = " << endl << B << endl << " P = " << endl << P << endl << " Q = " << endl << Q << endl << " E_integral = " << endl << E_integral << endl;
    //cout << " P_Jacobian = " << endl << P_Jacobian << endl << " Q_Jacobian = " << Q_Jacobian << endl;
	F_x0 = ((t2 - t1) / 2 * A + B) * x_Newton + (t2 - t1) / 2 * P + Q - (-(t2 - t1) / 2 * A + B) * x - (-(t2 - t1) / 2 * P_last + Q_last) - E_integral;
    Jacobian = (t2 - t1) / 2 * A + B + (t2 - t1) / 2 * P_Jacobian + Q_Jacobian;
    //cout << "Jacobian = " << endl << Jacobian << endl;
    //cout << "F  = " << endl << F << endl;
    //cout << endl;
}
#include <chrono>
//03-Trapezoidal
void Solver_TR::solve(BaseNewton* MyNewton) {
	MyNewton_ = MyNewton;
	//auto start = std::chrono::steady_clock::now();
	dt_ = MyConfig_->Get_dt();
	t_end_ = MyConfig_->Get_t_end();
	//ѭ��01
    for (int i = 0; i < t_end_ / dt_; i++) {
		//04-09-Trapezoidal
		//ѭ��02-05
		Perform_BaseNewton_solver(i * dt_, (i + 1) * dt_);

        //MyNewton->Perform_BaseNewton(MyConfig_, MyCircuit_, this, x_Newton, i * MyConfig_->Get_dt(), (i + 1) * MyConfig->Get_dt());
        x = x_Newton;
        Q_last = Q;
        P_last = P;
        /*-----------------------------------*/
		//10-Trapezoidal
		//ѭ��06
        //Solver::saveCircuitVars();
		Solver::x_result_vec_.push_back(x);
    }
	//auto end = std::chrono::steady_clock::now();

	//auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//cout << "solve������ʱ:" << time.count() / 1000 << "����" << endl;
}

void Solver_TR::Perform_BaseNewton_solver(double t1, double t2)
{
	int Max_Iteration_times = 1000;
	double Convergence_limit = 0.0001;
	int Iteration_times = 0;


	for (int Iteration_times = 0; Iteration_times < Max_Iteration_times; Iteration_times++)
	{
		//05-08-EulerBackward-Trapezoidal
		//ѭ��-03-05
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
	//	//ѭ��-03-05
	//	processJacobianAndF(t1, t2);
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