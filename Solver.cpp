#include "Solver.h"
#include <chrono>
#include <direct.h> 
#include <filesystem> 
#include <io.h>

Solver::Solver() {

}

void Solver::processTimeInvariantDeviceMatrix(Circuit* MyCircuit) {
    for (int m = 0; m < MyCircuit->vecTimeInvariantDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit->vecTimeInvariantDeviceInfo[m];
		vector<int> index = current_info.xIndex;
        int xCountTemp = current_info.xCount;

        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subB = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);

        MyCircuit->vecTimeInvariantDevice[m]->getTimeInvariantSubMatrix(subA, subB);

        for (int i = 0; i < xCountTemp; i++) {
            for (int j = 0; j < xCountTemp; j++) {
                int row_num = index[i];
                int col_num = index[j];
                A(row_num, col_num) += subA(i,j);
                B(row_num, col_num) += subB(i,j);
            }
        }
        //cout << "A=" << endl << A << endl;
    }
}

void Solver::processTimeVariantDeviceMatrix(Circuit* MyCircuit, const Eigen::VectorXd& x_pr) {
    for (int m = 0; m < MyCircuit->vecTimeVariantDevice.size(); m++) {
		DeviceInfoStr current_info = MyCircuit->vecTimeVariantDeviceInfo[m];
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
            nodeValue(i) = x_pr(index[i]);
        }
        //cout << "nodeValue = " << endl << nodeValue << endl;
        MyCircuit->vecTimeVariantDevice[m]->getTimeVariantSubMatrix(nodeValue, subA, subB, subP, subPJacobian, subQ, subQJacobian);
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
        //cout << "A=" << endl << A << endl;
    }
}

void Solver::processExcitationDeivceMatrix(Circuit* MyCircuit, double t) {

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

int Solver::getSize() {
    return size;
}

Solver::~Solver() {
}