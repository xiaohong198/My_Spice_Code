#pragma once
#include "TabulatedIVCurveDevice.h"

class SurgeArrester :public TabulatedIVCurveDevice
{
private:
	int iv_count_;
	double* i_list_;
	double* v_list_;//Ĭ�ϰ��մ�С��������
public:
	SurgeArrester();
	~SurgeArrester();

	double F(double);
	double G(double);
	void GetSubPandPJacobian(const Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&);
	int GetReturnPrime();
	void SetDeviceInfo(map<string, int>&);
	void SetInputData(InputStr, map<string, int>&);
	DeviceInfoStr GetDeviceInfo();
	string GetInstanceName();
};
