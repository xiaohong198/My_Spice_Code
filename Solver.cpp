#include "Solver.h"
#include <chrono>
#include <direct.h> 
#include <filesystem> 
#include <io.h>
#include <typeinfo>

Solver::Solver(Configuration* MyConfig, Circuit* MyCircuit) {
	MyConfig_ = MyConfig;
	MyCircuit_ = MyCircuit;

	size = MyCircuit_->matrixDimension;
	/*---------------------矩阵初始化---------------------*/
	A = Eigen::MatrixXd::Zero(size, size);
	A_mid = Eigen::MatrixXd::Zero(size, size);

	B = Eigen::MatrixXd::Zero(size, size);
	B_mid = Eigen::MatrixXd::Zero(size, size);

	P_Jacobian = Eigen::MatrixXd::Zero(size, size);
	P_Jacobian_mid = Eigen::MatrixXd::Zero(size, size);

	Q_Jacobian = Eigen::MatrixXd::Zero(size, size);
	Q_Jacobian_mid = Eigen::MatrixXd::Zero(size, size);

	E = Eigen::VectorXd::Zero(size);
	E_mid = Eigen::VectorXd::Zero(size);

	P = Eigen::VectorXd::Zero(size);
	P_mid = Eigen::VectorXd::Zero(size);

	P_last = Eigen::VectorXd::Zero(size);
	P_last_mid = Eigen::VectorXd::Zero(size);

	Q = Eigen::VectorXd::Zero(size);
	Q_mid = Eigen::VectorXd::Zero(size);

	Q_last = Eigen::VectorXd::Zero(size);
	Q_last_mid = Eigen::VectorXd::Zero(size);

	//F = Eigen::VectorXd::Zero(size);

	x = Eigen::VectorXd::Zero(size);
	x_Newton = Eigen::VectorXd::Zero(size);
	F_x0 = Eigen::VectorXd::Zero(size);
	Jacobian = Eigen::MatrixXd::Zero(size, size);

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
	//x(1) = 20;

	Solver::x_result_vec_.push_back(Solver::x);

	processSetZeroABE();
	processTimeInvariantDeviceMatrix();//TimeInvariantDevice其实只用填一次
	A_mid = A;
	B_mid = B;
	E_mid = E;
}

void Solver::processGroundedNodeEqu() {
	A.row(0).setZero();
	A(0, 0) = 1;
	B.row(0).setZero();
	P_Jacobian.row(0).setZero();
	Q_Jacobian.row(0).setZero();

	E.row(0).setZero();
	P.row(0).setZero();
	P_last.row(0).setZero();
	Q.row(0).setZero();
	Q_last.row(0).setZero();
}

void Solver::processSetZero() {
	P_Jacobian.setZero();
	Q_Jacobian.setZero();
	P.setZero();
	P_last.row(0).setZero();
	Q.setZero();
	Q_last.setZero();
}

void Solver::processSetZeroABE() {
	A.setZero();
	B.setZero();
	E.setZero();
}

void Solver::processExcitationDeivceMatrix(int _index) {
	double t1 = _index * dt_;
	double t2 = (_index + 1) * dt_;
	for (int m = 0; m < MyCircuit_->vecExcitationDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit_->vecExcitationDeviceInfo[m];
		vector<int> index = current_info.xIndex;
		int xCountTemp = current_info.xCount;

		Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);;
		Eigen::VectorXd subE = Eigen::VectorXd::Zero(xCountTemp);
		
		string child_name = typeid(*this).name();
		if (child_name == "class Solver_TR")
		{
			MyCircuit_->vecExcitationDevice[m]->getExcitationIntegralSubMatrix(subA, subE, t1, t2);
		}
		else if (child_name == "class Solver_EulerBackward")
		{
			MyCircuit_->vecExcitationDevice[m]->getExcitationSubMatrix(subA, subE, t2);
		}

		for (int i = 0; i < xCountTemp; i++) {
			E(index[i]) += subE(i);
			for (int j = 0; j < xCountTemp; j++) {
				A(index[i], index[j]) += subA(i, j);
			}
		}
	}
}

void Solver::processTimeInvariantDeviceMatrix() {
    for (int m = 0; m < MyCircuit_->vecTimeInvariantDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit_->vecTimeInvariantDeviceInfo[m];
		vector<int> index = current_info.xIndex;
        int xCountTemp = current_info.xCount;

        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subB = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);

		MyCircuit_->vecTimeInvariantDevice[m]->getTimeInvariantSubMatrix(subA, subB);

        for (int i = 0; i < xCountTemp; i++) {
            for (int j = 0; j < xCountTemp; j++) {
                int row_num = index[i];
                int col_num = index[j];
                A(row_num, col_num) += subA(i,j);
                B(row_num, col_num) += subB(i,j);
            }
        }
    }
}

void Solver::processTimeVariantDeviceMatrix() {
    for (int m = 0; m < MyCircuit_->vecTimeVariantDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit_->vecTimeVariantDeviceInfo[m];
		vector<int> index = current_info.xIndex;
        int xCountTemp = current_info.xCount;

        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subB = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subPJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subQJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::VectorXd subP = Eigen::VectorXd::Zero(xCountTemp);
        Eigen::VectorXd subQ = Eigen::VectorXd::Zero(xCountTemp);
        Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(xCountTemp);

        for (int i = 0; i < xCountTemp; i++) {
            nodeValue(i) = x_Newton(index[i]);
        }

		MyCircuit_->vecTimeVariantDevice[m]->getTimeVariantSubMatrix(nodeValue, subA, subB, subP, subPJacobian, subQ, subQJacobian);
        for (int i = 0; i < xCountTemp; i++) {
			int index_current = index[i];
            P(index_current) += subP(i);
            Q(index_current) += subQ(i);
            for (int j = 0; j < xCountTemp; j++) {
				int index_current_j = index[j];
                A(index_current, index_current_j) += subA(i, j);
                B(index_current, index_current_j) += subB(i, j);
                P_Jacobian(index_current, index_current_j) += subPJacobian(i, j);
                Q_Jacobian(index_current, index_current_j) += subQJacobian(i, j);
            }
        }
    }
}

void Solver::saveCircuitVars() {
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/CircuitVars.txt";

	int re = _access(output_dir_Path.c_str(), 0);
	switch (re)
	{
		case -1:
			_mkdir(output_dir_Path.c_str());				//创建目录
			break;
		default:
			remove(outputPath.c_str());//删除文件
			//_rmdir(output_dir_Path.c_str());//删除目录
			_mkdir(output_dir_Path.c_str());				//创建目录
			break;
	}

	std::stringstream ss;
	//循环-06
	for (auto iter : x_result_vec_)
	{
		for (int i = 0; i < size; i++)
		{
			ss << std::setprecision(8) << iter(i)<<',';
		}
		ss << '\n';
	}

	ofstream OpenF3(outputPath, ios::trunc | ios::out);
	OpenF3 << ss.str();
	OpenF3.close();
	x_result_vec_.clear();
}


Solver::~Solver() {
}