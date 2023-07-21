#include "TabulatedIVCurveDevice.h"

TabulatedIVCurveDevice::TabulatedIVCurveDevice() {
}
TabulatedIVCurveDevice::~TabulatedIVCurveDevice() {
}
void TabulatedIVCurveDevice::Fitting(int _iv_count, double* _i_list, double* _v_list) {
	for (int i = 0; i < _iv_count - 1; i++) {
		*(i_difference_ + i) = *(_i_list + i + 1) - *(_i_list + i);
	}
	for (int i = 0; i < _iv_count - 1; i++) {
		*(v_difference_ + i) = *(_v_list + i + 1) - *(_v_list + i);
	}

	Eigen::MatrixXd mat(_iv_count, _iv_count);
	Eigen::VectorXd rhs(_iv_count);
	Eigen::VectorXd sol(_iv_count);//m向量
	for (int i = 0; i < _iv_count; i++) {
		for (int j = 0; j < _iv_count; j++) {
			mat(i, j) = 0;
		}
	}
	mat(0, 0) -= *(v_difference_ + 1);
	mat(0, 1) += *(v_difference_)+*(v_difference_ + 1);
	mat(0, 2) -= *(v_difference_);
	mat(_iv_count - 1, _iv_count - 1) -= *(v_difference_ + _iv_count - 3);
	mat(_iv_count - 1, _iv_count - 2) += *(v_difference_ + _iv_count - 3) + *(v_difference_ + _iv_count - 2);
	mat(_iv_count - 1, _iv_count - 3) -= *(v_difference_ + _iv_count - 2);
	for (int i = 1; i < _iv_count - 1; i++) {
		mat(i, i - 1) += *(v_difference_ + i - 1);
		mat(i, i) += 2 * (*(v_difference_ + i - 1) + *(v_difference_ + i));
		mat(i, i + 1) += *(v_difference_ + i);
	}
	rhs(0) = 0;
	rhs(_iv_count - 1) = 0;
	for (int i = 1; i < _iv_count - 1; i++) {
		rhs(i) = 6 * (*(i_difference_ + i) / *(v_difference_ + i) - *(i_difference_ + i - 1) / *(v_difference_ + i - 1));
	}
	sol = mat.lu().solve(rhs);//求出m向量
	for (int i = 0; i < _iv_count - 1; i++) {
		*(coeff_0_ + i) = *(_i_list + i);
		*(coeff_1_ + i) = *(i_difference_ + i) / *(v_difference_ + i) - *(v_difference_ + i) * sol(i) / 2 - *(v_difference_ + i) * (sol(i + 1) - sol(i)) / 6;
		*(coeff_2_ + i) = sol(i) / 2;
		*(coeff_3_ + i) = (sol(i + 1) - sol(i)) / (6 * *(v_difference_ + i));
	}//给三次多项式系数赋值
}