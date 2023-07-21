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
	map<string, InputStr> user_compare_;//key：实例名 value：实例参数 input获取到的给到用户的数据
	map<string, int> port_compare_;//key：端口号 value：端口号的值 端口号对照,一般 从input获取到的里面只有n0=0
	map<string, int> hint_compare_;//key：端口号 value：初值 端口号初值对照
	map<string, PlotStr> plot_compare_;//key：文件名 value：plot参数 plot参数对照
	map<string, vector<int>> device_additional_compare_;//key：实例名 value：新增值对照
	map<string, vector<string>> device_port_compare_;//key：实例名 value：端口号列表

public:
	Circuit();
	~Circuit();
};
