#include "PWLVoltageSource.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>  
using namespace std;
PWLVoltageSource::PWLVoltageSource() {
	tCount = 5;
	tList = new double[tCount];
	vList = new double[tCount];

	vList[0] = 0;
	vList[1] = 0;
	vList[2] = 5;
	vList[3] = 5;
	vList[4] = 0;

	tList[0] = 0;
	tList[1] = 0.9e-6;
	tList[2] = 1.0e-6;
	tList[3] = 3.0e-6;
	tList[4] = 3.1e-6;
}

PWLVoltageSource::~PWLVoltageSource() {
	delete[] tList;
	delete[] vList;
}

double PWLVoltageSource::eFunction(double t) {
	//std::map<double, double> sort_map;
	//std::vector<double> sort_vec;
	//std::vector<double> sort_vec_t;
	//sort_vec_t.push_back(t);
	//for (auto i = 0; i < tCount; i++)
	//{
	//	sort_vec.push_back(tList[i]);
	//	sort_vec_t.push_back(tList[i]);
	//	sort_map.insert(pair<double, double>(tList[i], vList[i]));
	//}
	//sort(sort_vec.begin(), sort_vec.end());
	//sort(sort_vec_t.begin(), sort_vec_t.end());

	//double PSL;
	//if (t < *sort_vec.begin())
	//{
	//	PSL = sort_map[*sort_vec.begin()];
	//}
	//else if (t >= *(sort_vec.end() - 1))
	//{
	//	PSL = sort_map[*(sort_vec.end() - 1)];
	//}
	//else
	//{
	//	auto iter = find(sort_vec_t.begin(), sort_vec_t.end(), t);
	//	PSL = (sort_map[*(iter + 1)] - sort_map[*(iter - 1)]) / (*(iter + 1) - *(iter - 1)) * (t - *(iter - 1)) + sort_map[*(iter - 1)];
	//}

	//return PSL;
	if (t < tList[0]) {
		return vList[0];
	}
	else if (t >= tList[tCount-1]) {
		return vList[tCount-1];
	}
	else {
		for (int i = 1; i < tCount; i++) {
			if (t < tList[i]) {
				return ((vList[i] - vList[i - 1]) / (tList[i] - tList[i - 1]) * (t - tList[i - 1]) + vList[i - 1]);
			}
		}
	}

}

//void PWLVoltageSource::getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double t) {
//	subA.setZero();
//	subA(0, 2) = 1;
//	subA(1, 2) = -1;
//	subA(2, 0) = 1;
//	subA(2, 1) = -1;
//	subE.setZero();
//	subE(2) = eFunction(t);
//}

double PWLVoltageSource::setIntegration(double* tList) {
	//std::vector<double> sort_vec_t;
	//sort_vec_t.push_back(t1);
	//sort_vec_t.push_back(t2);
	//for (auto i = 0; i < tCount; i++)
	//{
	//	sort_vec_t.push_back(tList[i]);
	//}
	//sort(sort_vec_t.begin(), sort_vec_t.end());

	//double PSLIntegral = 0;

	//auto iter_t1 = find(sort_vec_t.begin(), sort_vec_t.end(), t1);
	//auto iter_t2 = find(sort_vec_t.begin(), sort_vec_t.end(), t2);

	//auto mid = iter_t2 - iter_t1;

	//if (mid == 0)
	//{
	//	PSLIntegral = (eFunction(t1) + eFunction(t2)) * (t2 - t1) / 2;
	//}
	//else
	//{
	//	for (auto iter_mid = 0; iter_mid <= mid - 1; iter_mid++)
	//	{
	//		double t_mid = *(iter_t2 - iter_mid);
	//		double t_mid_before = *(iter_t2 - iter_mid - 1);
	//		PSLIntegral = (eFunction(t_mid) + eFunction(t_mid_before)) * (t_mid - t_mid_before) / 2;
	//		PSLIntegral += PSLIntegral;
	//	}
	//}
	double t1 = tList[0];
	double t2 = tList[1];
	double PSLIntegral = 0;
	double vt1 = eFunction(t1);
	double vt2 = eFunction(t2);
	//默认t1<t2;
	int Locationt1 = tCount;
	int Locationt2 = tCount;
	for (int i = 0; i < tCount; i++) {//定位t1
		if (t1 < tList[i]) {
			Locationt1 = i;
			break;
		}
	}
	for (int i = 0; i < tCount; i++) {//定位t2
		if (t2 < tList[i]) {
			Locationt2 = i;
			break;
		}
	}
	if (Locationt1 == Locationt2) {
		PSLIntegral = (vt1 + vt2) * (t2 - t1) / 2;
	}
	else {
		PSLIntegral += (vt1 + vList[Locationt1]) * (tList[Locationt1] - t1) * 0.5;
		PSLIntegral += (vt2 + vList[Locationt2 - 1]) * (t2 - tList[Locationt2 - 1]) * 0.5;
		for (int i = Locationt1; i < Locationt2-1; i++) {//如果t1和t2在相邻区间，这个循环不会运行
			PSLIntegral += (vList[i] + vList[i + 1]) * (tList[i + 1] - tList[i]) * 0.5;
		}
	}
	return PSLIntegral;
}

//void PWLVoltageSource::getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double t1, double t2) {
//	subA.setZero();
//	subA(0, 2) = 1;
//	subA(1, 2) = -1;
//	subA(2, 0) = 1;
//	subA(2, 1) = -1;
//	subEIntegral.setZero();
//	//subEIntegral(2) = setIntegration(t1, t2);
//	subEIntegral(2) = (eFunction(t1) + eFunction(t2)) / 2 * (t2 - t1);
//}

void PWLVoltageSource::getSubA(Eigen::MatrixXd& subA) {
	subA.setZero();
	subA(0, 2) = 1;
	subA(1, 2) = -1;
	subA(2, 0) = 1;
	subA(2, 1) = -1;
}

void PWLVoltageSource::getSubEIntegral(Eigen::VectorXd& subEIntegral, double* tList) {
	subEIntegral.setZero();
	subEIntegral(2) = (eFunction(tList[0]) + eFunction(tList[1])) / 2 * (tList[1] - tList[0]);
}