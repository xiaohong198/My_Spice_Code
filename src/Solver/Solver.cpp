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
	/*---------------------�����ʼ��---------------------*/
	A = Eigen::MatrixXd::Zero(size, size);

	B = Eigen::MatrixXd::Zero(size, size);

	P_Jacobian = Eigen::MatrixXd::Zero(size, size);

	Q_Jacobian = Eigen::MatrixXd::Zero(size, size);

	E = Eigen::VectorXd::Zero(size);
	E_Integral = Eigen::VectorXd::Zero(size);

	P = Eigen::VectorXd::Zero(size);

	P_last = Eigen::VectorXd::Zero(size);

	Q = Eigen::VectorXd::Zero(size);

	Q_last = Eigen::VectorXd::Zero(size);

	C = Eigen::MatrixXd::Zero(size, size);

	//F = Eigen::VectorXd::Zero(size);

	x = Eigen::VectorXd::Zero(size);
	x_Newton = Eigen::VectorXd::Zero(size);
	F_x0 = Eigen::VectorXd::Zero(size);
	Jacobian = Eigen::MatrixXd::Zero(size, size);
	
	dt_ = MyConfig_->Get_dt();
	t_end_ = MyConfig_->Get_t_end();

	/*--------------------------------------------------*/
	/*-----x�ĳ�ֵ-----*/
	//x(0) = 0;
	//x(1) = 20;//19.4736
	//x(2) = 0;
	//x(3) = 0;//-1.94736
	for (int i = 0; i < size; i++) {
		x(i) = 0;
	}
	x(1) = 20;
	x_Newton = x;
	Solver::x_result_vec_.push_back(Solver::x);

	processA();//A��Bֻ��һ�ξͲ�����
	processB();//A��Bֻ��һ�ξͲ�����

}
void Solver::Process(vector<int> _process)
{
	vector <Device*> current_device;
	for (auto iter : _process)
	{
		if (iter == PrimeA)
		{
			current_device = MyCircuit_->vecDeviceForMatrixA;
		}
		if (iter == PrimeB)
		{
			current_device = MyCircuit_->vecDeviceForMatrixB;
		}
		if (iter == PrimeC)
		{
			current_device = MyCircuit_->vecDeviceForMatrixC;
		}
		if (iter == PrimeP)
		{
			current_device = MyCircuit_->vecDeviceForMatrixP;
		}
		if (iter == PrimeQ)
		{
			current_device = MyCircuit_->vecDeviceForMatrixQ;
		}
		if (iter == PrimeE)
		{
			current_device = MyCircuit_->vecDeviceForVectorE;
		}

		for (auto iter : current_device) {
			DeviceInfoStr current_info = iter->getDeviceInfo_();
			vector<int> index = current_info.xIndex;
			int xCountTemp = index.size();
			Eigen::MatrixXd sub = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
			iter->getSubB(sub);
			for (int i = 0; i < xCountTemp; i++) {
				for (int j = 0; j < xCountTemp; j++) {
					int row_num = index[i];
					int col_num = index[j];
					B(row_num, col_num) += sub(i, j);
				}
			}
		}
	}
}

void Solver::processA() {//ɨ����������
	for (auto iter : MyCircuit_->vecDeviceForMatrixA) {
		DeviceInfoStr current_info = iter->getDeviceInfo_();
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

void Solver::processB() {//ɨ����������
	for (auto iter : MyCircuit_->vecDeviceForMatrixB) {
		DeviceInfoStr current_info = iter->getDeviceInfo_();
		vector<int> index = current_info.xIndex;
		int xCountTemp = index.size();
        Eigen::MatrixXd subB = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
		iter->getSubB(subB);
        for (int i = 0; i < xCountTemp; i++) {
            for (int j = 0; j < xCountTemp; j++) {
				int row_num = index[i];
				int col_num = index[j];
                B(row_num, col_num) += subB(i,j);
            }
        }
    }
}

void Solver::processEIntegral(double* tList) {
	for (auto iter : MyCircuit_->vecDeviceForVectorE) {
		DeviceInfoStr current_info = iter->getDeviceInfo_();
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

void Solver::processP() {//ɨ��TimeVariantDevice
	for (auto iter : MyCircuit_->vecDeviceForMatrixP) {
		DeviceInfoStr current_info = iter->getDeviceInfo_();
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

void Solver::processQ() {//ɨ��TimeVariantDevice
	for (auto iter : MyCircuit_->vecDeviceForMatrixQ) {
		DeviceInfoStr current_info = iter->getDeviceInfo_();
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

void Solver::processC() {//ɨ��TimeVariantDevice
	for (auto iter : MyCircuit_->vecDeviceForMatrixQ) {
		DeviceInfoStr current_info = iter->getDeviceInfo_();
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
    E_Integral.row(0).setZero();
    P.row(0).setZero();
    if (P_last.size() != 0) {
        P_last.row(0).setZero();
    }
    Q.row(0).setZero();
    Q_last.row(0).setZero();
}

void Solver::processSetZero() {
    P_Jacobian.setZero();
    Q_Jacobian.setZero();
    P.setZero();
    P_last.setZero();
    Q.setZero();
    Q_last.setZero();
    C.setZero();
}


void Solver::solve() 
{
	int num_t = t_end_ / dt_;
    for (int i = 0; i < num_t; i++) {
        double tList[2] = { i * dt_,(i + 1) * dt_ };
        E_Integral.setZero();
        processEIntegral(tList);//��E_Integral��ÿ��ʱ��ѭ����һ�Σ�������Newton��ѭ��
		MyNewton_->Perform_BaseNewton();
		x = x_Newton;
        Q_last = Q;
		Solver::x_result_vec_.push_back(Solver::x);
    }
}

void Solver::saveCircuitVars() {
	// ��ȡ��ǰ·��
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/CircuitVars.txt";

	int re = _access(output_dir_Path.c_str(), 0);
	switch (re)
	{
	case -1:
		_mkdir(output_dir_Path.c_str());				//����Ŀ¼
		break;
	default:
		remove(outputPath.c_str());//ɾ���ļ�
		//_rmdir(output_dir_Path.c_str());//ɾ��Ŀ¼
		_mkdir(output_dir_Path.c_str());				//����Ŀ¼
		break;
	}

	std::stringstream ss;
	//ѭ��-06
	for (auto iter : x_result_vec_)
	{
		for (int i = 0; i < size; i++)
		{
			ss << std::setprecision(8) << iter(i) << ',';
		}
		ss << '\n';
	}

	ofstream OpenF3(outputPath, ios::trunc | ios::out);
	OpenF3 << ss.str();
	OpenF3.close();
	x_result_vec_.clear();
}

int Solver::getSize() {
    return size;
}

Solver::~Solver() {
}