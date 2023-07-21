#pragma once
#include "Device/Device.h"
#include "Device/Resistor.h"
#include "Device/Capacitor.h"
#include "Device/Inductor.h"
#include "Device/VsourceDC.h"
#include "Device/VsourceAC.h"
#include "Device/JsourceDC.h"
#include "Device/JsourceAC.h"
#include "Device/PWLVoltageSource.h"
#include "Device/Diode.h"
#include "Device/TabulatedIVCurveDevice.h"
#include "Device/SurgeArrester.h"
#include "Device/SpiceMosfet.h"
#include "Device/SpiceDiode.h"
#include "Input.h"
using namespace std;

class Circuit
{
public:
	int matrix_dimension_;
	vector <int> voltage_x_index_;
	vector <int> current_x_index_;
	vector <Device*> device_matrix_a_;
	vector <Device*> device_matrix_b_;
	vector <Device*> device_matrix_p_;
	vector <Device*> device_matrix_q_;
	vector <Device*> device_matrix_c_;
	vector <Device*> device_matrix_e_;

	Input* input_;
	Device* device_;
	map<string, InputStr> user_compare_;//key��ʵ���� value��ʵ������ input��ȡ���ĸ����û�������
	map<string, int> port_compare_;//key���˿ں� value���˿ںŵ�ֵ �˿ںŶ���,һ�� ��input��ȡ��������ֻ��n0=0
	map<string, int> hint_compare_;//key���˿ں� value����ֵ �˿ںų�ֵ����
	map<string, PlotStr> plot_compare_;//key���ļ��� value��plot���� plot��������
	map<string, vector<int>> device_additional_compare_;//key��ʵ���� value������ֵ����
	map<string, vector<string>> device_port_compare_;//key��ʵ���� value���˿ں��б�

public:
	Circuit();
	~Circuit();
};
