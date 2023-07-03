#include "Solver.h"
Solver::Solver(Configuration* MyConfig, Circuit* MyCircuit) {
	MyConfig_ = MyConfig;
	MyCircuit_ = MyCircuit;
	Output_ = new Output();
	size = MyCircuit_->matrixDimension;
	VoltageXIndex = MyCircuit_->VoltageXIndex;
	CurrentXIndex = MyCircuit_->CurrentXIndex;
	/*---------------------矩阵初始�?--------------------*/
	A = Eigen::MatrixXd::Zero(size, size);

	B = Eigen::MatrixXd::Zero(size, size);

	P_Jacobian = Eigen::MatrixXd::Zero(size, size);

	Q_Jacobian = Eigen::MatrixXd::Zero(size, size);

	//E = Eigen::VectorXd::Zero(size);
	E_Integral = Eigen::VectorXd::Zero(size);

	P = Eigen::VectorXd::Zero(size);

	P_s1 = Eigen::VectorXd::Zero(size);

	Q = Eigen::VectorXd::Zero(size);
	Q_s1 = Eigen::VectorXd::Zero(size);
	Q_s2 = Eigen::VectorXd::Zero(size);

	C = Eigen::MatrixXd::Zero(size, size);
	C_s1 = Eigen::MatrixXd::Zero(size, size);
	C_s2 = Eigen::MatrixXd::Zero(size, size);

	x = Eigen::VectorXd::Zero(size);
	x_s2 = Eigen::VectorXd::Zero(size);
	x_Newton = Eigen::VectorXd::Zero(size);
	F_x0 = Eigen::VectorXd::Zero(size);
	Jacobian = Eigen::MatrixXd::Zero(size, size);

	dt_ = MyConfig_->Get_dt();
	t_end_ = MyConfig_->Get_t_end();

	/*--------------------------------------------------*/
	/*-----mos1 paper-----*/
	//for (int i = 0; i < size; i++) {
	//	x(i) = 0;
	//}
	//x(1) = 52;
	//x(2) = 50;
	//x(3) = 48;
	//x(4) = 48;
	//x(5) = 50;
	//x(6) = 48;
	//x(7) = 50;
	//x(12) = x(4);
	//x(13) = x(5);

	/*-----mos1 debug2-----*/
	//for (int i = 0; i < size; i++) {
	//	x(i) = 0;
	//}
	//x(1) = 52;//n1
	//x(6) = 50;//n2
	//x(4) = 50;//n3
	//x(3) = 50;//n4
	//x(2) = 50;//n5
	//x(7) = 50;//n6
	//x(8) = 50;//n7
	//
	//x(11) = x(3);//n12_Dp = D
	//x(12) = x(2);//n13_Sp = S
	//x(5) = 50;//n14

	/*----mos1 debug3---*/
	//for (int i = 0; i < size; i++) {
	//	x(i) = 0;
	//}
	//x(1) = 52;
	//x(2) = 50;
	//x(3) = 50;
	//x(4) = 50;
	//x(5) = 50;
	//x(6) = 50;
	//x(7) = 50;
	//x(12) = x(4);
	//x(13) = x(5);
	//x(14) = 50;
	//x(15) = x(5);
	//x(16) = x(4);


	/*-----mos1 debug2-----*/
	for (int i = 0; i < size; i++) {
		x(i) = 0;
	}
	x(5) = 52;//n1=52
	x(7) = 50;//n2=50
	x(3) = 50;//n3=50
	x(2) = 50;//n4=50
	x(4) = 50;//n5=50
	x(1) = 50;//n6=50
	x(8) = 50;//n7=50
	x(13) = 0;//n8_ipwl
	x(14) = 0;//n9_idc
	x(10) = 0;//n10_iLs
	x(9) = 0;//n11_iLd
	x(11) = x(3);//n12_Dp = D
	x(12) = x(2);//n13_Sp = S
	x(6) = 50;//n14=50
	x_s2 = x;
	x_Newton = x;
	Solver::x_result_vec_.push_back(Solver::x);

	processA();//A、B只填一次就不动�?

	processB();//A、B只填一次就不动�?
}

void Solver::processA() {//扫描所有器�?
	for (auto iter : MyCircuit_->vecDeviceForMatrixA) {
		DeviceInfoStr current_info = iter->getDeviceInfo();
		vector<int> index = current_info.xIndex;
		int xCountTemp = index.size();
		Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
		iter->getSubA(subA);
		for (int i = 0; i < xCountTemp; i++) {
			for (int j = 0; j < xCountTemp; j++) {
				int row_num = index[i];
				int col_num = index[j];
				A(row_num, col_num) += subA(i, j);
			}
		}
	}
}

void Solver::processB() {
	for (auto iter : MyCircuit_->vecDeviceForMatrixB) {
		DeviceInfoStr current_info = iter->getDeviceInfo();
		vector<int> index = current_info.xIndex;
		int xCountTemp = index.size();
		Eigen::MatrixXd subB = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
		iter->getSubB(subB);
		for (int i = 0; i < xCountTemp; i++) {
			for (int j = 0; j < xCountTemp; j++) {
				int row_num = index[i];
				int col_num = index[j];
				B(row_num, col_num) += subB(i, j);
			}
		}
	}
}

void Solver::processEIntegral(double* tList) {
	for (auto iter : MyCircuit_->vecDeviceForVectorE) {
		DeviceInfoStr current_info = iter->getDeviceInfo();
		vector<int> index = current_info.xIndex;
		int xCountTemp = index.size();
		Eigen::VectorXd subEIntegral = Eigen::VectorXd::Zero(xCountTemp);
		iter->getSubEIntegral(subEIntegral, tList);
		for (int i = 0; i < xCountTemp; i++) {
			int row_num = index[i];
			E_Integral(row_num) += subEIntegral(i);
		}
	}
}

void Solver::processP() {
	for (auto iter : MyCircuit_->vecDeviceForMatrixP) {
		DeviceInfoStr current_info = iter->getDeviceInfo();
		vector<int> index = current_info.xIndex;
		int xCountTemp = index.size();
		Eigen::MatrixXd subPJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
		Eigen::VectorXd subP = Eigen::VectorXd::Zero(xCountTemp);
		Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(xCountTemp);
		for (int i = 0; i < xCountTemp; i++) {
			int row_num = index[i];

			nodeValue(i) = x_Newton(row_num);
		}
		iter->getSubPandPJacobian(nodeValue, subP, subPJacobian);
		for (int i = 0; i < xCountTemp; i++) {
			int row_num = index[i];
			P(row_num) += subP(i);
			for (int j = 0; j < xCountTemp; j++) {
				int col_num = index[j];
				P_Jacobian(row_num, col_num) += subPJacobian(i, j);
			}
		}
	}
}

void Solver::processQ() {
	for (auto iter : MyCircuit_->vecDeviceForMatrixQ) {
		DeviceInfoStr current_info = iter->getDeviceInfo();
		vector<int> index = current_info.xIndex;
		int xCountTemp = index.size();
		Eigen::MatrixXd subQJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
		Eigen::VectorXd subQ = Eigen::VectorXd::Zero(xCountTemp);
		Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(xCountTemp);
		for (int i = 0; i < xCountTemp; i++) {
			int row_num = index[i];

			nodeValue(i) = x_Newton(row_num);
		}
		iter->getSubQandQJacobian(nodeValue, subQ, subQJacobian);
		for (int i = 0; i < xCountTemp; i++) {
			int row_num = index[i];
			Q(row_num) += subQ(i);
			for (int j = 0; j < xCountTemp; j++) {
				int col_num = index[j];
				Q_Jacobian(row_num, col_num) += subQJacobian(i, j);
			}
		}
	}
}

void Solver::processC() {
	for (auto iter : MyCircuit_->vecDeviceForMatrixQ) {
		DeviceInfoStr current_info = iter->getDeviceInfo();
		vector<int> index = current_info.xIndex;
		int xCountTemp = index.size();
		Eigen::MatrixXd subC = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
		Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(xCountTemp);
		for (int i = 0; i < xCountTemp; i++) {
			int row_num = index[i];

			nodeValue(i) = x_Newton(row_num);
		}
		iter->getSubC(nodeValue, subC);
		for (int i = 0; i < xCountTemp; i++) {
			int row_num = index[i];
			for (int j = 0; j < xCountTemp; j++) {
				int col_num = index[j];
				C(row_num, col_num) += subC(i, j);
			}
		}
	}
}

void Solver::processGroundedNodeEqu() {//���񻹿��Ծ��򣿰�A B Eժ��ȥ��
	A.row(0).setZero();
	A(0, 0) = 1;
	B.row(0).setZero();
	P_Jacobian.row(0).setZero();
	Q_Jacobian.row(0).setZero();
	C.row(0).setZero();
	//C_s1.row(0).setZero();
	E_Integral.row(0).setZero();
	P.row(0).setZero();
	//P_s1.row(0).setZero();
	//if (P_s1.size() != 0) {
	//    P_s1.row(0).setZero();
	//}
	Q.row(0).setZero();
	//Q_s1.row(0).setZero();
}

void Solver::processSetZero() {
	P_Jacobian.setZero();
	Q_Jacobian.setZero();
	P.setZero();
	//P_s1.setZero();
	Q.setZero();
	//Q_s1.setZero();
	C.setZero();
}

void Solver::solve()
{
	int num_t = t_end_ / dt_;
	for (int i = 0; i < num_t; i++) {
		double tList[2] = { i * dt_,(i + 1) * dt_ };
		E_Integral.setZero();
		processEIntegral(tList);//填E_Integral，每个时间循环填一次，不参与Newton的循�?

		MyNewton_->Perform_Newton();
		x_s2 = x;
		x = x_Newton;
		P_s1 = P;
		Q_s2 = Q_s1;
		Q_s1 = Q;
		C_s2 = C_s1;
		C_s1 = C;
		x_result_vec_.push_back(x);
	}
}

void Solver::SaveCircuitVars()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/CircuitVars.txt";
	Output_->_VectorXd_size = size;
	Output_->SaveTxt(outputPath, x_result_vec_);
}

int Solver::getSize() {
	return size;
}

Solver::~Solver() {
}

/*
BasicNewton EulerBackward 233
BasicNewton TrapezoidalIntegration 96530
BankRoseDampingNewton EulerBackward 27723
BankRoseDampingNewton TrapezoidalIntegration 31399
*/