#include "PWLVoltageSource.h"
#include <algorithm>
#include <iostream>
#include <map>  
using namespace std;
PWLVoltageSource::PWLVoltageSource() {
	tCount = 5;
	tList = new double[tCount];
	vList = new double[tCount];
	vList[0] = 0;
	vList[1] = 0;
	vList[2] = 20;
	vList[3] = 20;
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
	
	std::map<double,double> sort_map;
	std::vector<double> sort_vec;
	std::vector<double> sort_vec_t;
	sort_vec_t.push_back(t);
	for (auto i = 0; i < tCount; i++)
	{
		sort_vec.push_back(tList[i]);
		sort_vec_t.push_back(tList[i]);
		sort_map.insert(pair<double, double>(tList[i], vList[i]));
	}
	sort(sort_vec.begin(), sort_vec.end());
	sort(sort_vec_t.begin(), sort_vec_t.end());

	double PSL;
	//if (t < tList[0]) {
	//    PSL = vList[0];
	//}
	//else if (t >= tList[0] && t < tList[tCount - 1]) {
	//    for (int i = 0; i < tCount-1; i++) {
	//        if (t >= tList[i] && t < tList[i+1])
	//            PSL = (vList[i+1] - vList[i]) / (tList[i+1] - tList[i]) * (t - tList[i]) + vList[i];
	//    }
	//}
	//else {
	//    PSL = vList[tCount - 1];
	//}

	if (t <= *sort_vec.begin())
	{
		PSL = sort_map[*sort_vec.begin()];
	}
	else if (t >= *(sort_vec.end() - 1))
	{
		PSL = sort_map[*(sort_vec.end() - 1)];
	}
	else
	{
		auto iter = find(sort_vec_t.begin(), sort_vec_t.end(), t);
		PSL = (sort_map[*(iter + 1)] - sort_map[*(iter - 1)]) / (*(iter + 1) - *(iter - 1)) * (t - *(iter - 1)) + sort_map[*(iter - 1)];
	
	}

	return PSL;
}

void PWLVoltageSource::getExcitationSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subE, double t) {
	subA.setZero();
	subA(0, 2) = 1;
	subA(1, 2) = -1;
	subA(2, 0) = 1;
	subA(2, 1) = -1;
	subE.setZero();
	subE(2) = eFunction(t);
}

double PWLVoltageSource::setIntegration(double t1, double t2) {
	std::vector<double> sort_vec_t;
	sort_vec_t.push_back(t1);
	sort_vec_t.push_back(t2);
	for (auto i = 0; i < tCount; i++)
	{
		sort_vec_t.push_back(tList[i]);
	}
	sort(sort_vec_t.begin(), sort_vec_t.end());

	double PSLIntegral = 0;

	auto iter_t1 = find(sort_vec_t.begin(), sort_vec_t.end(), t1);
	auto iter_t2 = find(sort_vec_t.begin(), sort_vec_t.end(), t2);

	auto mid = iter_t2 - iter_t1;

	if (mid == 0)
	{
		PSLIntegral = (eFunction(t1) + eFunction(t2))*(t2 - t1) / 2;
	}
	else
	{
		for (auto iter_mid = 0; iter_mid <= mid - 1; iter_mid++)
		{
			double t_mid= *(iter_t2 - iter_mid);
			double t_mid_before = *(iter_t2 - iter_mid - 1);
			PSLIntegral = (eFunction(t_mid) + eFunction(t_mid_before))*(t_mid - t_mid_before) / 2;
			PSLIntegral += PSLIntegral;
		}
	}

	//if (t1 < tList[0]) {
	//	if (t2 >= tList[0] && t2 < tList[1]) {
	//		PSLIntegral = 0.5 * (vList[1] - vList[0]) / (tList[1] - tList[0]) * pow((t2 - tList[0]), 2) + vList[0] * (t2 - tList[0]);
	//	}
	//	else if (t2 >= tList[1] && t2 < tList[2]) {
	//		PSLIntegral = (vList[0] + vList[1]) * (tList[1] - tList[0]) / 2 + 0.5 * (vList[2] - vList[1]) / (tList[2] - tList[1]) * pow((t2 - tList[1]), 2) + vList[1] * (t2 - tList[1]);
	//	}
	//	else if (t2 >= tList[2] && t2 < tList[3]) {
	//		PSLIntegral = (vList[0] + vList[1]) * (tList[1] - tList[0]) / 2 + (vList[1] + vList[2]) * (tList[2] - tList[1]) / 2 + 0.5 * (vList[3] - vList[2]) / (tList[3] - tList[2]) * pow((t2 - tList[2]), 2) + vList[2] * (t2 - tList[2]);
	//	}
	//	else if (t2 >= tList[3] && t2 < tList[4]) {
	//		PSLIntegral = (vList[0] + vList[1]) * (tList[1] - tList[0]) / 2 + (vList[1] + vList[2]) * (tList[2] - tList[1]) / 2 + (vList[2] + vList[3]) * (tList[3] - tList[2]) / 2 + 0.5 * (vList[4] - vList[3]) / (tList[4] - tList[3]) * pow((t2 - tList[3]), 2) + vList[3] * (t2 - tList[3]);
	//	}
	//	else if (t2 >= tList[4]) {
	//		PSLIntegral = (vList[0] + vList[1]) * (tList[1] - tList[0]) / 2 + (vList[1] + vList[2]) * (tList[2] - tList[1]) / 2 + (vList[2] + vList[3]) * (tList[3] - tList[2]) / 2 + (vList[3] + vList[4]) * (tList[4] - tList[3]) / 2 + (t2 - tList[4]) * vList[4];
	//	}
	//}
	//else if (t1 >= tList[0] && t1 < tList[1]) {
	//	if (t2 < tList[1]) {
	//		PSLIntegral = 0.5 * (vList[1] - vList[0]) / (tList[1] - tList[0]) * pow((t2 - t1), 2) + ((vList[1] - vList[0]) / (tList[1] - tList[0]) * (t1 - tList[0]) + vList[0]) * (t2 - t1);
	//	}
	//	else if (t2 >= tList[1] && t2 < tList[2]) {
	//		PSLIntegral = 0.5 * (vList[1] - vList[0]) / (tList[1] - tList[0]) * pow((t1 - tList[1]), 2) + vList[1] * (t1 - tList[1]) + 0.5 * (vList[2] - vList[1]) / (tList[2] - tList[1]) * pow((t2 - tList[1]), 2) + vList[1] * (t2 - tList[1]);
	//	}
	//	else if (t2 >= tList[2] && t2 < tList[3]) {
	//		PSLIntegral = 0.5 * (vList[1] - vList[0]) / (tList[1] - tList[0]) * pow((t1 - tList[1]), 2) + vList[1] * (t1 - tList[1]) + (vList[1] + vList[2]) * (tList[2] - tList[1]) / 2 + 0.5 * (vList[3] - vList[2]) / (tList[3] - tList[2]) * pow((t2 - tList[2]), 2) + vList[2] * (t2 - tList[2]);
	//	}
	//	else if (t2 >= tList[3] && t2 < tList[4]) {
	//		PSLIntegral = 0.5 * (vList[1] - vList[0]) / (tList[1] - tList[0]) * pow((t1 - tList[1]), 2) + vList[1] * (t1 - tList[1]) + (vList[1] + vList[2]) * (tList[2] - tList[1]) / 2 + (vList[2] + vList[3]) * (tList[3] - tList[2]) / 2 + 0.5 * (vList[4] - vList[3]) / (tList[4] - tList[3]) * pow((t2 - tList[3]), 2) + vList[3] * (t2 - tList[3]);
	//	}
	//	else if (t2 >= tList[4]) {
	//		PSLIntegral = 0.5 * (vList[1] - vList[0]) / (tList[1] - tList[0]) * pow((t1 - tList[1]), 2) + vList[1] * (t1 - tList[1]) + (vList[1] + vList[2]) * (tList[2] - tList[1]) / 2 + (vList[2] + vList[3]) * (tList[3] - tList[2]) / 2 + (vList[3] + vList[4]) * (tList[4] - tList[3]) / 2 + (t2 - tList[4]) * vList[4];
	//	}
	//}
	//else if (t1 >= tList[1] && t1 < tList[2]) {

	//}
	return PSLIntegral;
}

void PWLVoltageSource::getExcitationIntegralSubMatrix(Eigen::MatrixXd& subA, Eigen::VectorXd& subEIntegral, double t1, double t2) {
	subA.setZero();
	subA(0, 2) = 1;
	subA(1, 2) = -1;
	subA(2, 0) = 1;
	subA(2, 1) = -1;
	subEIntegral.setZero();
	subEIntegral(2) = setIntegration(t1, t2);
}