#pragma once
#include <fstream>
#include <vector>
#include "Device.h"
#include "structDeviceInfo.h"
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Vsource_DC.h"
#include "Vsource_AC.h"
#include "Jsource.h"
#include "Diode.h"
#include "MOA.h"
#include "TabulatedIVCurveDevice.h"
#include "SurgeArrester.h"

using namespace std;
class Device;
class structDeviceInfo;
class Circuit
{
	friend class Solver;
	friend class Solver_EulerBackward;
	friend class Solver_TR;
protected:
	int timeInvariantDeviceCount;
	int timeVariantDeviceCount;
	int excitationDeviceCount;
	int nodeCount;
	int AdditaionalxCount;//未知量x中有多少个除节点电压以外的变量
	int matrixDimension;

		//vector <Device*> vecDevice;
	vector <Device*> vecTimeInvariantDevice;
	vector <Device*> vecTimeVariantDevice;
	vector <Device*> vecExcitationDevice;//是直流源、交流源这种激励源E(t)单独一类，受控源依然放在前两类中

	//vector <structDeviceInfo*> vecDeviceInfo;
	vector <structDeviceInfo*> vecTimeInvariantDeviceInfo;
	vector <structDeviceInfo*> vecTimeVariantDeviceInfo;
	vector <structDeviceInfo*> vecExcitationDeviceInfo;

public:
	Circuit();
	~Circuit();
	//得到vector <Device*> f和deviceCount
	void Read_Inputfile();
};

