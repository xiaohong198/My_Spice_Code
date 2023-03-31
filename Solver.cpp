#include "Solver.h"

Solver::Solver() {

}

void Solver::processTimeInvariantDeviceMatrix(Circuit* MyCircuit) {
    for (int m = 0; m < MyCircuit->vecTimeInvariantDevice.size(); m++) {
        int xCountTemp = MyCircuit->vecTimeInvariantDeviceInfo[m]->getXCount();
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subB = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        MyCircuit->vecTimeInvariantDevice[m]->getTimeInvariantSubMatrix(subA, subB);
        for (int i = 0; i < xCountTemp; i++) {
            for (int j = 0; j < xCountTemp; j++) {
                int row_num = *(MyCircuit->vecTimeInvariantDeviceInfo[m]->getxIndex() + i);
                int col_num = *(MyCircuit->vecTimeInvariantDeviceInfo[m]->getxIndex() + j);
                A(row_num, col_num) += subA(i,j);
                B(row_num, col_num) += subB(i,j);
            }
        }
        //cout << "A=" << endl << A << endl;
    }
}

void Solver::processTimeVariantDeviceMatrix(Circuit* MyCircuit, const Eigen::VectorXd& x_pr) {
    for (int m = 0; m < MyCircuit->vecTimeVariantDevice.size(); m++) {
        int xCountTemp = MyCircuit->vecTimeVariantDeviceInfo[m]->getXCount();
        Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subPJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::MatrixXd subQJacobian = Eigen::MatrixXd::Zero(xCountTemp, xCountTemp);
        Eigen::VectorXd subP = Eigen::VectorXd::Zero(xCountTemp);
        Eigen::VectorXd subQ = Eigen::VectorXd::Zero(xCountTemp);
        Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(xCountTemp);
        for (int i = 0; i < xCountTemp; i++) {
            nodeValue(i) = x_pr(*(MyCircuit->vecTimeVariantDeviceInfo[m]->getxIndex() + i));
        }
        //cout << "nodeValue = " << endl << nodeValue << endl;
        MyCircuit->vecTimeVariantDevice[m]->getTimeVariantSubMatrix(nodeValue, subA, subP, subPJacobian, subQ, subQJacobian);
        for (int i = 0; i < xCountTemp; i++) {
            P(*(MyCircuit->vecTimeVariantDeviceInfo[m]->getxIndex() + i)) += subP(i);
            Q(*(MyCircuit->vecTimeVariantDeviceInfo[m]->getxIndex() + i)) += subQ(i);
            for (int j = 0; j < xCountTemp; j++) {
                A(*(MyCircuit->vecTimeVariantDeviceInfo[m]->getxIndex() + i), *(MyCircuit->vecTimeVariantDeviceInfo[m]->getxIndex() + j)) += subA(i, j);
                P_Jacobian(*(MyCircuit->vecTimeVariantDeviceInfo[m]->getxIndex() + i), *(MyCircuit->vecTimeVariantDeviceInfo[m]->getxIndex() + j)) += subPJacobian(i, j);
                Q_Jacobian(*(MyCircuit->vecTimeVariantDeviceInfo[m]->getxIndex() + i), *(MyCircuit->vecTimeVariantDeviceInfo[m]->getxIndex() + j)) += subQJacobian(i, j);
            }
        }
        //cout << "A=" << endl << A << endl;
    }
}

void Solver::processExcitationDeivceMatrix(Circuit* MyCircuit, double t) {

}
#include <direct.h> 
#include <filesystem> 

void Solver::saveCircuitVars() {
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string outputPath = path + "/CircuitVarsData/CircuitVars.txt";
	// 自动创建文件夹
	std::filesystem::path path_txt(outputPath);
	std::filesystem::create_directories(path_txt.parent_path());
    std::ofstream out_circuit_vars(outputPath, std::ios::app);
    
	for (int i = 0; i < size; i++)
    {
        out_circuit_vars << std::setprecision(8) << x(i) << ',';
    }
    out_circuit_vars << std::endl;
    out_circuit_vars.close();
}

int Solver::getSize() {
    return size;
}

Solver::~Solver() {
}