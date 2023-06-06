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
#include "Device/SpiceDiode.h" 
#include "Input.h"
using namespace std;

class Circuit
{

public:
	int matrixDimension;
	vector <int> VoltageXIndex;
	vector <int> CurrentXIndex;
	vector <Device*> vecDeviceForMatrixA;
	vector <Device*> vecDeviceForMatrixB;
	vector <Device*> vecDeviceForMatrixP;
	vector <Device*> vecDeviceForMatrixQ;
	vector <Device*> vecDeviceForMatrixC;
	vector <Device*> vecDeviceForVectorE;


private:
	Input* Input_;
	Device* Device_;
	map<string, InputStr> UserParameter_;
	map<string, int> PortCompareMap;
	map<string, int> HintCompareMap;


public:
	Circuit();
	~Circuit();
	void SetPortCompare();

};
