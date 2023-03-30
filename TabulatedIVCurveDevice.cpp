#include "TabulatedIVCurveDevice.h"
#include <Eigen/Dense>
#include <Eigen/LU>
#include <cmath>
#include <iostream>
using namespace std;
TabulatedIVCurveDevice::TabulatedIVCurveDevice() {

}
TabulatedIVCurveDevice::~TabulatedIVCurveDevice() {

}
void TabulatedIVCurveDevice::fitting(int IVCount, double* IList, double* VList, double* IDifference, double* VDifference, double* Coeff0, double* Coeff1, double* Coeff2, double* Coeff3) {
	for (int i = 0; i < IVCount - 1; i++) {
		*(IDifference+i) = *(IList+i+1) - *(IList+i);
	}
	for (int i = 0; i < IVCount - 1; i++) {
		*(VDifference+i) = *(VList+i+1) - *(VList+i);
	}

	Eigen::MatrixXd mat(IVCount, IVCount);
	Eigen::VectorXd rhs(IVCount);
	Eigen::VectorXd sol(IVCount);//m����
	for (int i = 0; i < IVCount; i++) {
		for (int j = 0; j < IVCount; j++) {
			mat(i, j) = 0;
		}
	}
	mat(0, 0) -= *(VDifference+1);
	mat(0, 1) += *(VDifference) + *(VDifference+1);
	mat(0, 2) -= *(VDifference);
	mat(IVCount - 1, IVCount - 1) -= *(VDifference + IVCount - 3);
	mat(IVCount - 1, IVCount - 2) += *(VDifference + IVCount - 3) + *(VDifference + IVCount - 2);
	mat(IVCount - 1, IVCount - 3) -= *(VDifference + IVCount - 2);
	for (int i = 1; i < IVCount - 1; i++) {
		mat(i, i - 1) += *(VDifference+i-1);
		mat(i, i) += 2 * (*(VDifference+i-1) + *(VDifference+i));
		mat(i, i + 1) += *(VDifference+i);
	}
	rhs(0) = 0;
	rhs(IVCount - 1) = 0;
	for (int i = 1; i < IVCount - 1; i++) {
		rhs(i) = 6 *(  *(IDifference + i)/ *(VDifference+i) - *(IDifference+i-1) / *(VDifference+i-1)  );
	}
	/*for (int i = 0; i < IVCount; i++) {
		cout << "IList[" << i << "]:" << *(IList+i) << endl;
	}
	for (int i = 0; i < IVCount; i++) {
		cout << "VList[" << i << "]:" << *(VList + i) << endl;
	}
	for (int i = 0; i < IVCount - 1; i++) {
		cout << "IDifference[" << i << "]:" << *(IDifference + i) << endl;
	}
	for (int i = 0; i < IVCount - 1; i++) {
		cout << "VDifference[" << i << "]:" << *(VDifference + i) << endl;
	}
	for (int i = 0; i < IVCount ; i++) {
		cout << "rhs(" << i << "):" << rhs(i) << endl;
	}
	for (int i = 0; i < IVCount; i++) {
		for (int j = 0; j < IVCount; j++) {
			cout << mat(i, j) << " ";
			if (j == IVCount - 1) {
				cout << endl;
			}
		}
	}*/
	sol = mat.lu().solve(rhs);//���m����
	for (int i = 0; i < IVCount - 1; i++) {
		*(Coeff0 + i) = *(IList + i);
		*(Coeff1 + i) = *(IDifference+i) / *(VDifference+i) - *(VDifference+i) * sol(i) / 2 - *(VDifference+i) * (sol(i + 1) - sol(i)) / 6;
		*(Coeff2 + i) = sol(i) / 2;
		*(Coeff3 + i) = (sol(i + 1) - sol(i)) / (6 * *(VDifference+i));
	}//�����ζ���ʽϵ����ֵ
	/*for (int i = 0; i < IVCount; i++) {
		cout << "sol(" << i << "):" << sol(i) << endl;
	}
	for (int i = 0; i < IVCount - 1; i++) {
		cout << "Coeff0[" << i << "]:" << Coeff0[i] << endl;
	}
	for (int i = 0; i < IVCount - 1; i++) {
		cout << "Coeff1[" << i << "]:" << Coeff1[i] << endl;
	}
	for (int i = 0; i < IVCount - 1; i++) {
		cout << "Coeff2[" << i << "]:" << Coeff2[i] << endl;
	}
	for (int i = 0; i < IVCount - 1; i++) {
		cout << "Coeff3[" << i << "]:" << Coeff3[i] << endl;
	}*/
}
double TabulatedIVCurveDevice::f(double V) {
	if (V < this->VList[0]) {
		return this->Coeff0[0] + this->Coeff1[0] * (V - this->VList[0]) + this->Coeff2[0] * pow(V - this->VList[0], 2) + this->Coeff3[0] * pow(V - this->VList[0], 3);
	}
	else if (V >= this->VList[IVCount - 1]) {
		return this->Coeff0[IVCount-2] + this->Coeff1[IVCount - 2] * (V - this->VList[IVCount - 2]) + this->Coeff2[IVCount - 2] * pow(V - this->VList[IVCount - 2], 2) + this->Coeff3[IVCount - 2] * pow(V - this->VList[IVCount - 2], 3);
	}
	else {
		for (int i = 0; i < IVCount - 1; i++) {
			if (this->VList[i] <= V && V < this->VList[i + 1]) {
				return this->Coeff0[i] + this->Coeff1[i] * (V - this->VList[i]) + this->Coeff2[i] * pow(V - this->VList[i], 2) + this->Coeff3[i] * pow(V - this->VList[i], 3);
			}
		}
	cout << "TabulatedIVCurveDevide goes wrong!" << endl;
	exit(0);
	return 1;
	}
}
double TabulatedIVCurveDevice::G(double V) {
	if (V < this->VList[0]) {
		return this->Coeff1[0] + 2 * this->Coeff2[0] * (V - this->VList[0]) + 3 * this->Coeff3[0] * pow(V - this->VList[0], 2);
	}
	else if (V >= this->VList[IVCount - 1]) {
		return this->Coeff1[IVCount - 2] + 2 * this->Coeff2[IVCount - 2] * (V - this->VList[IVCount - 2]) + 3 * this->Coeff3[IVCount - 2] * pow(V - this->VList[IVCount - 2], 2);
	}
	else {
		for (int i = 0; i < IVCount - 1; i++) {
			if (this->VList[i] <= V && V < this->VList[i + 1]) {
				return this->Coeff1[i] + 2 * this->Coeff2[i] * (V - this->VList[i]) + 3 * this->Coeff3[i] * pow(V - this->VList[i], 2);
			}
		}
	cout << "TabulatedIVCurveDevide goes wrong!" << endl;
	exit(0);
	return 1;
	}
}
void TabulatedIVCurveDevice::getTimeVariantSubMatrix(const Eigen::VectorXd& nodeValue, Eigen::MatrixXd& subA, Eigen::VectorXd& subP, Eigen::MatrixXd& subPJacobian, Eigen::VectorXd& subQ, Eigen::MatrixXd& subQJacobian) {
	subA.setZero();
	double V = nodeValue(0) - nodeValue(1);
	subP.setZero();
	subP(0) = f(V);
	subP(1) = -f(V);
	subPJacobian.setZero();
	subPJacobian(0, 0) = G(V);
	subPJacobian(0, 1) = -G(V);
	subPJacobian(1, 0) = -G(V);
	subPJacobian(1, 1) = G(V);
	subQ.setZero();
	subQJacobian.setZero();
}