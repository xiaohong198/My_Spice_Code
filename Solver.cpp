#include "Solver.h"
#include <chrono>
#include <direct.h> 
#include <filesystem> 
#include <io.h>

//最后弄
Solver::Solver() {

}
//06-EulerBackward-Trapezoidal
void Solver::processTimeInvariantDeviceMatrix(Circuit* MyCircuit) {

	//auto start = std::chrono::steady_clock::now();


	//循环-03
    for (int m = 0; m < MyCircuit->vecTimeInvariantDevice.size(); m++) {
		structDeviceInfo* current_info = MyCircuit->vecTimeInvariantDeviceInfo[m];
		int * index = current_info->getxIndex();
        int xCountTemp = current_info->getXCount();
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subB = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        MyCircuit->vecTimeInvariantDevice[m]->getTimeInvariantSubMatrix(subA, subB);
        for (int i = 0; i < xCountTemp; i++) {
            for (int j = 0; j < xCountTemp; j++) {
                int row_num = *(index + i);
                int col_num = *(index + j);
                A(row_num, col_num) += subA(i,j);
                B(row_num, col_num) += subB(i,j);
            }
        }
        //cout << "A=" << endl << A << endl;
    }


	//auto end = std::chrono::steady_clock::now();

	//auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//cout << "processTimeInvariantDeviceMatrix程序用时:" << time.count() / 1000 << "毫秒" << endl;


}
//08-EulerBackward-Trapezoidal
void Solver::processTimeVariantDeviceMatrix(Circuit* MyCircuit, const Eigen::VectorXd& x_pr) {
   
	//auto start = std::chrono::steady_clock::now();
	//循环-05
	for (int m = 0; m < MyCircuit->vecTimeVariantDevice.size(); m++) {
		structDeviceInfo* current_info = MyCircuit->vecTimeVariantDeviceInfo[m];
		int* index = current_info->getxIndex();
        int xCountTemp = current_info->getXCount();
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subPJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subQJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::VectorXd subP = Eigen::VectorXd::Zero(xCountTemp);
        Eigen::VectorXd subQ = Eigen::VectorXd::Zero(xCountTemp);
        Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(xCountTemp);
        for (int i = 0; i < xCountTemp; i++) {

            nodeValue(i) = x_pr(*(index + i));
        }
        //cout << "nodeValue = " << endl << nodeValue << endl;
        MyCircuit->vecTimeVariantDevice[m]->getTimeVariantSubMatrix(nodeValue, subA, subP, subPJacobian, subQ, subQJacobian);
        for (int i = 0; i < xCountTemp; i++) {
            P(*(index + i)) += subP(i);
            Q(*(index + i)) += subQ(i);
            for (int j = 0; j < xCountTemp; j++) {
                A(*(index + i), *(index + j)) += subA(i, j);
                P_Jacobian(*(index + i), *(index + j)) += subPJacobian(i, j);
                Q_Jacobian(*(index + i), *(index + j)) += subQJacobian(i, j);
            }
        }
        //cout << "A=" << endl << A << endl;
    }


	//auto end = std::chrono::steady_clock::now();

	//auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//cout << "processTimeVariantDeviceMatrix程序用时:" << time.count() / 1000 << "毫秒" << endl;


}

void Solver::processExcitationDeivceMatrix(int _index) {

}

//应该把所有数据先存在内存里最后再存txt 这个函数应该出循环
//10-EulerBackward-Trapezoidal
void Solver::saveCircuitVars() {
	//auto start = std::chrono::steady_clock::now();
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/CircuitVars.txt";

	//// 自动创建文件夹
	//if (_access(output_dir_Path.c_str(), 0) == -1)//如果文件夹不存在
	//{
	//	_mkdir(output_dir_Path.c_str());				//创建目录
	//}
	//else
	//{
	//	remove(outputPath.c_str());//删除文件
	//	//_rmdir(output_dir_Path.c_str());//删除目录
	//	_mkdir(output_dir_Path.c_str());				//创建目录
	//}
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

	//auto end = std::chrono::steady_clock::now();

	//auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//cout << "saveCircuitVars程序用时:" << time.count() / 1000 << "毫秒" << endl;

}

int Solver::getSize() {
    return size;
}

Solver::~Solver() {
}