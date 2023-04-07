#include "Solver.h"
#include <chrono>
#include <direct.h> 
#include <filesystem> 
#include <io.h>

Solver::Solver() {

}

void Solver::processTimeInvariantDeviceMatrix(Circuit* MyCircuit) {
    for (int m = 0; m < MyCircuit->vecTimeInvariantDevice.size(); m++) {
        int xCountTemp = MyCircuit->vecTimeInvariantDeviceInfo[m].xCount;
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subB = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        MyCircuit->vecTimeInvariantDevice[m]->getTimeInvariantSubMatrix(subA, subB);
        for (int i = 0; i < xCountTemp; i++) {
            for (int j = 0; j < xCountTemp; j++) {
                int row_num = MyCircuit->vecTimeInvariantDeviceInfo[m].xIndex[i];
                int col_num = MyCircuit->vecTimeInvariantDeviceInfo[m].xIndex[j];
                A(row_num, col_num) += subA(i,j);
                B(row_num, col_num) += subB(i,j);
            }
        }
        //cout << "A=" << endl << A << endl;
    }
}

void Solver::processTimeVariantDeviceMatrix(Circuit* MyCircuit, const Eigen::VectorXd& x_pr) {
    for (int m = 0; m < MyCircuit->vecTimeVariantDevice.size(); m++) {
        int xCountTemp = MyCircuit->vecTimeVariantDeviceInfo[m].xCount;
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subPJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subQJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::VectorXd subP = Eigen::VectorXd::Zero(xCountTemp);
        Eigen::VectorXd subQ = Eigen::VectorXd::Zero(xCountTemp);
        Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(xCountTemp);
        for (int i = 0; i < xCountTemp; i++) {
            nodeValue(i) = x_pr(MyCircuit->vecTimeVariantDeviceInfo[m].xIndex[i]);
        }
        //cout << "nodeValue = " << endl << nodeValue << endl;
        MyCircuit->vecTimeVariantDevice[m]->getTimeVariantSubMatrix(nodeValue, subA, subP, subPJacobian, subQ, subQJacobian);
        for (int i = 0; i < xCountTemp; i++) {
            P(MyCircuit->vecTimeVariantDeviceInfo[m].xIndex[i]) += subP(i);
            Q(MyCircuit->vecTimeVariantDeviceInfo[m].xIndex[i]) += subQ(i);
            for (int j = 0; j < xCountTemp; j++) {
                A(MyCircuit->vecTimeVariantDeviceInfo[m].xIndex[i], MyCircuit->vecTimeVariantDeviceInfo[m].xIndex[j]) += subA(i, j);
                P_Jacobian(MyCircuit->vecTimeVariantDeviceInfo[m].xIndex[i], MyCircuit->vecTimeVariantDeviceInfo[m].xIndex[j]) += subPJacobian(i, j);
                Q_Jacobian(MyCircuit->vecTimeVariantDeviceInfo[m].xIndex[i], MyCircuit->vecTimeVariantDeviceInfo[m].xIndex[j]) += subQJacobian(i, j);
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

	// 自动创建文件夹
	if (_access(output_dir_Path.c_str(), 0) == -1)//如果文件夹不存在
	{
		_mkdir(output_dir_Path.c_str());				//创建目录
	}
	else
	{
		remove(outputPath.c_str());//删除文件
		//_rmdir(output_dir_Path.c_str());//删除目录
		_mkdir(output_dir_Path.c_str());				//创建目录
	}
	std::ofstream out_circuit_vars(outputPath, std::ios::app);

	//循环-06
	for (auto iter : x_result_vec_)
	{
		for (int i = 0; i < size; i++)
		{
			out_circuit_vars << std::setprecision(8) << iter(i) << ',';
		}
		out_circuit_vars << std::endl;
	}

	out_circuit_vars.close();
	x_result_vec_.clear();

}

int Solver::getSize() {
    return size;
}

Solver::~Solver() {
}