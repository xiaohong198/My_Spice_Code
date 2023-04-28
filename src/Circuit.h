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

	int nodeCount;
	int AdditaionalxCount;//未知量x中有多少个除节点电压以外的变量
	int matrixDimension;


	vector <Device*> vecDeviceForMatrixA;
	vector <Device*> vecDeviceForMatrixB;
	vector <Device*> vecDeviceForMatrixP;
	vector <Device*> vecDeviceForMatrixQ;
	vector <Device*> vecDeviceForMatrixC;
	vector <Device*> vecDeviceForVectorE;
	vector <Device*> vecDevice;

	vector<InputDataStr> input_vec_;//存放读取结果（暂时）


private:
	Input* Input_;
	Device* Device_;
	DeviceInfoStr DeviceInfo_;


public:
	Circuit();
	~Circuit();
	void SetClassVec();

};

