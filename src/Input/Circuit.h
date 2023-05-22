#pragma once
#include "Device/Device.h"
#include "Device/Resistor.h"
#include "Device/Capacitor.h"
#include "Device/Inductor.h"
#include "Device/Vsource_DC.h"
#include "Device/Vsource_AC.h"
#include "Device/Jsource_DC.h"
#include "Device/Jsource_AC.h"
#include "Device/PWLVoltageSource.h"
#include "Device/Diode.h"
#include "Device/TabulatedIVCurveDevice.h"
#include "Device/SurgeArrester.h"
#include "Device/SpiceMosfet.h"
#include "Device/SpiceMosLevel1Test.h"
#include "Device/SpiceDiode.h" 
#include "Input.h"

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


private:
	Input* Input_;
	Device* Device_;
	DeviceInfoStr DeviceInfo_;


public:
	Circuit();
	~Circuit();
	void SetClassVec();

};

