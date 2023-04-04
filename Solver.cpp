#include "Solver.h"
#include <chrono>
#include <direct.h> 
#include <filesystem> 
#include <io.h>

//���Ū
Solver::Solver() {

}
//06-EulerBackward-Trapezoidal
void Solver::processTimeInvariantDeviceMatrix(Circuit* MyCircuit) {

	//auto start = std::chrono::steady_clock::now();


	//ѭ��-03
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

	//cout << "processTimeInvariantDeviceMatrix������ʱ:" << time.count() / 1000 << "����" << endl;


}
//08-EulerBackward-Trapezoidal
void Solver::processTimeVariantDeviceMatrix(Circuit* MyCircuit, const Eigen::VectorXd& x_pr) {
   
	//auto start = std::chrono::steady_clock::now();
	//ѭ��-05
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

	//cout << "processTimeVariantDeviceMatrix������ʱ:" << time.count() / 1000 << "����" << endl;


}

void Solver::processExcitationDeivceMatrix(int _index) {

}

//Ӧ�ð����������ȴ����ڴ�������ٴ�txt �������Ӧ�ó�ѭ��
//10-EulerBackward-Trapezoidal
void Solver::saveCircuitVars() {
	//auto start = std::chrono::steady_clock::now();
	// ��ȡ��ǰ·��
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/CircuitVars.txt";

	//// �Զ������ļ���
	//if (_access(output_dir_Path.c_str(), 0) == -1)//����ļ��в�����
	//{
	//	_mkdir(output_dir_Path.c_str());				//����Ŀ¼
	//}
	//else
	//{
	//	remove(outputPath.c_str());//ɾ���ļ�
	//	//_rmdir(output_dir_Path.c_str());//ɾ��Ŀ¼
	//	_mkdir(output_dir_Path.c_str());				//����Ŀ¼
	//}
    std::ofstream out_circuit_vars(outputPath, std::ios::app);
    
	//ѭ��-06
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

	//cout << "saveCircuitVars������ʱ:" << time.count() / 1000 << "����" << endl;

}

int Solver::getSize() {
    return size;
}

Solver::~Solver() {
}