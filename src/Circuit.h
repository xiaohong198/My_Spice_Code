#pragma once
#include "Device.h"
#include "structDeviceInfo.h"
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Vsource_DC.h"
#include "Vsource_AC.h"
#include "Jsource_DC.h"
#include "Jsource_AC.h"
#include "PWLVoltageSource.h"
#include "Diode.h"
#include "MOA.h"
#include "TabulatedIVCurveDevice.h"
#include "SurgeArrester.h"
#include "SpiceMosfet.h"
#include "SpiceMosLevel1Test.h"
#include "SpiceDiode.h" 
#include "Input.h"

//#include <boost/algorithm/string.hpp>

using namespace std;

class Device;
class structDeviceInfo;
class Circuit
{
	friend class Solver;
	friend class Solver_EulerBackward;
	friend class Solver_TR;
protected:
	//int timeInvariantDeviceCount;
	int timeVariantDeviceCount;
	int excitationDeviceCount;
	int DeviceCount;
	int nodeCount;
	int AdditaionalxCount;//未知量x中有多少个除节点电压以外的变量
	int matrixDimension;

	//vector <Device*> vecTimeInvariantDevice;
	//vector <Device*> vecTimeVariantDevice;
	//vector <Device*> vecExcitationDevice;//是直流源、交流源这种激励源E(t)单独一类，受控源依然放在前两类中
	vector <Device*> vecTimeVariantDevice;
	vector <Device*> vecExcitationDevice;//是直流源、交流源这种激励源E(t)单独一类，受控源依然放在前两	
	vector <Device*> vecDevice;

	//vector <structDeviceInfo*> vecDeviceInfo;
	vector <DeviceInfoStr> vecTimeInvariantDeviceInfo;
	vector <DeviceInfoStr> vecTimeVariantDeviceInfo;
	vector <DeviceInfoStr> vecExcitationDeviceInfo;
	vector <DeviceInfoStr> vecDeviceInfo;
	//vector <structDeviceInfo*> vecTimeInvariantDeviceInfo;
	//vector <structDeviceInfo*> vecTimeVariantDeviceInfo;
	//vector <structDeviceInfo*> vecExcitationDeviceInfo;


	vector <DeviceInfoStr> vecDeviceForMatrixA;
	vector <DeviceInfoStr> vecDeviceForMatrixB;
	vector <DeviceInfoStr> vecDeviceForMatrixP;
	vector <DeviceInfoStr> vecDeviceForMatrixQ;
	vector <DeviceInfoStr> vecDeviceForMatrixC;
	vector <DeviceInfoStr> vecDeviceForVectorE;
	
	vector<InputDataStr> input_vec_;//存放读取结果（暂时）


private:
	Input* Input_;
	Device* Device_;
	DeviceInfoStr DeviceInfo_;


public:
	Circuit();
	~Circuit();
	//得到vector <Device*> f和deviceCount

};

