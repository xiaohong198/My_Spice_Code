#include "Circuit.h"
#include <iostream>
#include <fstream>
#include <direct.h> 
#include <filesystem> 
#include <io.h>
#define byte my_byte
#include <windows.h>

using namespace std;
Circuit::Circuit() {
	//Read_InputIni();
    //Read_Inputfile();

/*---------------单相全桥不控整流电路Rectifier---------------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 2;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 5;
    //
    //for (int i = 0; i < 4; i++) {
    //    vecTimeVariantDevice.push_back(new Diode());
    //    vecTimeVariantDeviceInfo.push_back(new structDeviceInfo());
    //    vecTimeVariantDeviceInfo[i]->deviceType = 'D';
    //    vecTimeVariantDeviceInfo[i]->deviceIndexPerClass = i;
    //    vecTimeVariantDeviceInfo[i]->xCount = 2;
    //}
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 3;
    //vecTimeVariantDeviceInfo[1]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[1]->xIndex[1] = 3;
    //vecTimeVariantDeviceInfo[2]->xIndex[0] = 0;
    //vecTimeVariantDeviceInfo[2]->xIndex[1] = 2;
    //vecTimeVariantDeviceInfo[3]->xIndex[0] = 0;
    //vecTimeVariantDeviceInfo[3]->xIndex[1] = 1;

    //vecTimeInvariantDevice.push_back(new Inductor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'L';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 4;
    //vecTimeInvariantDeviceInfo[0]->xIndex[2] = 6;
    //vecTimeInvariantDevice[0]->setConstValue(1.0e-3);

    //vecTimeInvariantDevice.push_back(new Capacitor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[1]->deviceType = 'C';
    //vecTimeInvariantDeviceInfo[1]->deviceIndexPerClass = 1;
    //vecTimeInvariantDeviceInfo[1]->xCount = 2;
    //vecTimeInvariantDeviceInfo[1]->xIndex[0] = 4;
    //vecTimeInvariantDeviceInfo[1]->xIndex[1] = 0;
    //vecTimeInvariantDevice[1]->setConstValue(1.0e-4);

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[2]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[2]->deviceIndexPerClass = 2;
    //vecTimeInvariantDeviceInfo[2]->xCount = 2;
    //vecTimeInvariantDeviceInfo[2]->xIndex[0] = 4;
    //vecTimeInvariantDeviceInfo[2]->xIndex[1] = 0;
    //vecTimeInvariantDevice[2]->setConstValue(10);

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 5;
    //AdditaionalxCount = 2;
    //matrixDimension = nodeCount + AdditaionalxCount;

/*-------------------------交流源+Diode+RLC测试-------------------------------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 4;

    //vecTimeVariantDevice.push_back(new Diode());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeVariantDeviceInfo[0]->deviceType = 'D';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 2;

    //vecTimeInvariantDevice.push_back(new Inductor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'L';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 2;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[2] = 5;
    //vecTimeInvariantDevice[0]->setConstValue(1.0e-3);

    //vecTimeInvariantDevice.push_back(new Capacitor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[1]->deviceType = 'C';
    //vecTimeInvariantDeviceInfo[1]->deviceIndexPerClass = 1;
    //vecTimeInvariantDeviceInfo[1]->xCount = 2;
    //vecTimeInvariantDeviceInfo[1]->xIndex[0] = 3;
    //vecTimeInvariantDeviceInfo[1]->xIndex[1] = 0;
    //vecTimeInvariantDevice[1]->setConstValue(1.0e-4);

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[2]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[2]->deviceIndexPerClass = 2;
    //vecTimeInvariantDeviceInfo[2]->xCount = 2;
    //vecTimeInvariantDeviceInfo[2]->xIndex[0] = 3;
    //vecTimeInvariantDeviceInfo[2]->xIndex[1] = 0;
    //vecTimeInvariantDevice[2]->setConstValue(10);

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 4;
    //AdditaionalxCount = 2;
    //matrixDimension = nodeCount + AdditaionalxCount;

    /*-------------------------交流源Ramp 100t + 非线性电阻 + 电阻测试-------------------------------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 3;

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 2;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 2;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 0;
    //vecTimeInvariantDevice[0]->setConstValue(10);

    //vecTimeVariantDevice.push_back(new Diode());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeVariantDeviceInfo[0]->deviceType = 'D';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 2;

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 3;
    //AdditaionalxCount = 1;
    //matrixDimension = nodeCount + AdditaionalxCount;

 /*--------------交流源10sin(wt) + Diode 测试-------------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 2;

    //vecTimeVariantDevice.push_back(new Diode());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeVariantDeviceInfo[0]->deviceType = 'D';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 0;

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 2;
    //AdditaionalxCount = 1;
    //matrixDimension = nodeCount + AdditaionalxCount;

    ///*--------------交流源10sin(wt) + RLC 测试-------------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 4;

    //vecTimeInvariantDevice.push_back(new Inductor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'L';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 2;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[2] = 5;
    //vecTimeInvariantDevice[0]->setConstValue(1.0e-3);

    //vecTimeInvariantDevice.push_back(new Capacitor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[1]->deviceType = 'C';
    //vecTimeInvariantDeviceInfo[1]->deviceIndexPerClass = 1;
    //vecTimeInvariantDeviceInfo[1]->xCount = 2;
    //vecTimeInvariantDeviceInfo[1]->xIndex[0] = 3;
    //vecTimeInvariantDeviceInfo[1]->xIndex[1] = 0;
    //vecTimeInvariantDevice[1]->setConstValue(1.0e-4);

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[2]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[2]->deviceIndexPerClass = 2;
    //vecTimeInvariantDeviceInfo[2]->xCount = 2;
    //vecTimeInvariantDeviceInfo[2]->xIndex[0] = 3;
    //vecTimeInvariantDeviceInfo[2]->xIndex[1] = 0;
    //vecTimeInvariantDevice[2]->setConstValue(10);

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[3]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[3]->deviceIndexPerClass = 3;
    //vecTimeInvariantDeviceInfo[3]->xCount = 2;
    //vecTimeInvariantDeviceInfo[3]->xIndex[0] = 1;
    //vecTimeInvariantDeviceInfo[3]->xIndex[1] = 2;
    //vecTimeInvariantDevice[3]->setConstValue(10);

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 4;
    //AdditaionalxCount = 2;
    //matrixDimension = nodeCount + AdditaionalxCount;

    /*--------------MOA+Jsource 测试-------------*/
    //vecExcitationDevice.push_back(new Jsource());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'J';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 2;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 1;
    //vecExcitationDevice[0]->setConstValue(1.8);
    //
    //vecTimeVariantDevice.push_back(new MOA());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo);
    //vecTimeVariantDeviceInfo[0]->deviceType = 'MOA';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 0;
    //
    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 2;
    //AdditaionalxCount = 0;
    //matrixDimension = nodeCount + AdditaionalxCount;

    /*--------------SurgeArrester+Vsource_AC+R 测试-------------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 3;

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 2;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 2;
    //vecTimeInvariantDevice[0]->setConstValue(0.01);

    //vecTimeVariantDevice.push_back(new SurgeArrester());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo);
    //vecTimeVariantDeviceInfo[0]->deviceType = 'MOA';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 0;

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 3;
    //AdditaionalxCount = 1;
    //matrixDimension = nodeCount + AdditaionalxCount;

    /*---------测试--------*/
    //vecExcitationDevice.push_back(new PWLVoltageSource());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 2;
    ////vecExcitationDevice[0]->setConstValue(1);

    //vecTimeInvariantDevice.push_back(new Inductor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'L';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 0;
    //vecTimeInvariantDeviceInfo[0]->xIndex[2] = 3;
    //vecTimeInvariantDevice[0]->setConstValue(1);

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 2;
    //AdditaionalxCount = 2;
    //matrixDimension = nodeCount + AdditaionalxCount;

    /*-------Mos Level1测试-----*/
    //vecTimeVariantDevice.push_back(new SpiceMosLevel1Test());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeVariantDeviceInfo[0]->deviceType = 'M';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 6;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[2] = 3;
    //vecTimeVariantDeviceInfo[0]->xIndex[4] = 5;
    //vecTimeVariantDeviceInfo[0]->xIndex[3] = 4;
    //vecTimeVariantDeviceInfo[0]->xIndex[4] = 5;
    //vecTimeVariantDeviceInfo[0]->xIndex[5] = 6;

    //vecExcitationDevice.push_back(new Vsource_DC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 9;
    //vecExcitationDevice[0]->setConstValue(20);

    //vecExcitationDevice.push_back(new PWLVoltageSource());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[1]->deviceType = 'P';
    //vecExcitationDeviceInfo[1]->deviceIndexPerClass = 1;
    //vecExcitationDeviceInfo[1]->xCount = 3;
    //vecExcitationDeviceInfo[1]->xIndex[0] = 8;
    //vecExcitationDeviceInfo[1]->xIndex[1] = 5;
    //vecExcitationDeviceInfo[1]->xIndex[2] = 10;

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 2;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 8;
    //vecTimeInvariantDevice[0]->setConstValue(223.8e-2);

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[1]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[1]->deviceIndexPerClass = 1;
    //vecTimeInvariantDeviceInfo[1]->xCount = 2;
    //vecTimeInvariantDeviceInfo[1]->xIndex[0] = 7;
    //vecTimeInvariantDeviceInfo[1]->xIndex[1] = 0;
    //vecTimeInvariantDevice[1]->setConstValue(1.5e-3);

    //vecTimeInvariantDevice.push_back(new Inductor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[2]->deviceType = 'L';
    //vecTimeInvariantDeviceInfo[2]->deviceIndexPerClass = 2;
    //vecTimeInvariantDeviceInfo[2]->xCount = 3;
    //vecTimeInvariantDeviceInfo[2]->xIndex[0] = 5;
    //vecTimeInvariantDeviceInfo[2]->xIndex[1] = 7;
    //vecTimeInvariantDeviceInfo[2]->xIndex[2] = 11;
    //vecTimeInvariantDevice[2]->setConstValue(1.0e-9);

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 9;
    //AdditaionalxCount = 3;
    //matrixDimension = nodeCount + AdditaionalxCount;

    /*----------SpiceDiode测试---------*/
	DeviceInfoStr  DeviceInfo;
    vecExcitationDevice.push_back(new Vsource_AC());
	DeviceInfo.deviceType = 'V';
	DeviceInfo.deviceIndexPerClass = 0;
	DeviceInfo.xCount = 3;
	DeviceInfo.xIndex = { 1,0,5 };
	vecExcitationDeviceInfo.push_back(DeviceInfo);

    vecTimeVariantDevice.push_back(new SpiceDiode());
	DeviceInfo.deviceType = 'D';
	DeviceInfo.deviceIndexPerClass = 0;
	DeviceInfo.xCount = 3;
	DeviceInfo.xIndex = { 1,2,3 };
    vecTimeVariantDeviceInfo.push_back(DeviceInfo);


    vecTimeInvariantDevice.push_back(new Inductor());
	DeviceInfo.deviceType = 'L';
	DeviceInfo.deviceIndexPerClass = 0;
	DeviceInfo.xCount = 3;
	DeviceInfo.xIndex = { 3,4,6 };
    vecTimeInvariantDeviceInfo.push_back(DeviceInfo);
    vecTimeInvariantDevice[0]->setConstValue(1.0e-3);

    vecTimeInvariantDevice.push_back(new Capacitor());
	DeviceInfo.deviceType = 'C';
	DeviceInfo.deviceIndexPerClass = 1;
	DeviceInfo.xCount = 2;
	DeviceInfo.xIndex = { 4,0 };
    vecTimeInvariantDeviceInfo.push_back(DeviceInfo);
    vecTimeInvariantDevice[1]->setConstValue(1.0e-4);

    vecTimeInvariantDevice.push_back(new Resistor());
	DeviceInfo.deviceType = 'R';
	DeviceInfo.deviceIndexPerClass = 2;
	DeviceInfo.xCount = 2;
	DeviceInfo.xIndex = { 4,0 };
    vecTimeInvariantDeviceInfo.push_back(DeviceInfo);
    vecTimeInvariantDevice[2]->setConstValue(10);

    timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    timeVariantDeviceCount = vecTimeVariantDevice.size();
    excitationDeviceCount = vecExcitationDevice.size();
    nodeCount = 5;
    AdditaionalxCount = 2;
    matrixDimension = nodeCount + AdditaionalxCount;

    /*-----测试coding功能---*/
    //cout << endl;
}

void Circuit::Read_InputIni()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/Config";
	string outputPath = output_dir_Path + "/Input_Circuit_Diode_level.ini";

	string value;
	GetPrivateProfileStringA("section", "key", "default_value", &value[0], 256, "test.ini");
	std::cout << "value:" << value.c_str() << std::endl;

}

void Circuit::Read_Inputfile() {
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/Input_Circuit_Diode_level1.txt";

    ifstream fin(outputPath);
    string nowline;
    stringstream sstr;
    int last_sp;
    int nodeMax = 0;
    while (getline(fin, nowline)) {
        int i = 0;
        while (1) {
            if (nowline[i] == 32)
                break;
            i++;
        }//[i]为第一个空格

        int j;
        for (j = nowline.size() - 1; j > i; j--) {
            if (nowline[j] == 32) {
                break;
            }
        }//[j]为最后一个空格
        /*-------------------------------同时预填f,统计type-----------------------------------*/
        vecTimeInvariantDeviceInfo[excitationDeviceCount].deviceType = nowline[0];
        last_sp = i;
        switch (nowline[0]) {
        case 'R':
            vecTimeInvariantDevice.push_back(new Resistor());
            vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xCount = 2;
            for (int h = i + 2; h < j + 1; h++) {
                int portCount = 0;
                if (nowline[h] == ' ') {
                    sstr << nowline.substr(last_sp + 1, h - last_sp - 1);
                    sstr >> vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
                    if (vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount] > nodeMax)
                        nodeMax = vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
                    last_sp = h;
                    portCount++;
                }
            }
            vecTimeInvariantDevice[timeInvariantDeviceCount]->setConstValue(nowline[j+1] - '0');
            timeInvariantDeviceCount++;
            break;
        case 'C':
            vecTimeInvariantDevice.push_back(new Capacitor());
            vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xCount = 2;
            for (int h = i + 2; h < j + 1; h++) {
                int portCount = 0;
                if (nowline[h] == ' ') {
                    sstr << nowline.substr(last_sp + 1, h - last_sp - 1);
                    sstr >> vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
                    if (vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount] > nodeMax)
                        nodeMax = vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
                    last_sp = h;
                    portCount++;
                }
            }
            vecTimeInvariantDevice[timeInvariantDeviceCount]->setConstValue(nowline[j + 1] - '0');
            timeInvariantDeviceCount++;
            break;
        case 'L':
            vecTimeInvariantDevice.push_back(new Inductor());
            timeInvariantDeviceCount++;
            break;
        case 'V':
            vecExcitationDevice.push_back(new Vsource_DC());
            vecExcitationDeviceInfo[excitationDeviceCount].xCount = 3;
            vecExcitationDeviceInfo[excitationDeviceCount].additionalxCount = 1;
            for (int h = i + 2; h < j + 1; h++) {
                int portCount = 0;
                if (nowline[h] == ' ') {
                    sstr << nowline.substr(last_sp + 1, h - last_sp - 1);
                    sstr >> vecExcitationDeviceInfo[excitationDeviceCount].xIndex[portCount];
                    if (vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount] > nodeMax)
                        nodeMax = vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
                    last_sp = h;
                    portCount++;
                }
            }
            excitationDeviceCount++;

            break;
        //case 'J':
        //    vecExcitationDevice.push_back(new Jsource());
        //    excitationDeviceCount++;
        //    break;
        case 'D':
            vecTimeVariantDevice.push_back(new Diode());
            timeVariantDeviceCount++;
            break;
        }
    }

    int sumAdditionalxCount = 0;
    for (int i = 0; i < timeInvariantDeviceCount; i++) {
        if (vecTimeInvariantDeviceInfo[i].additionalxCount) {
            int vCount = vecTimeInvariantDeviceInfo[i].xCount - vecTimeInvariantDeviceInfo[i].additionalxCount;
            for (int j = 0; j < vecTimeInvariantDeviceInfo[i].additionalxCount; j++) {
                vecTimeInvariantDeviceInfo[i].xIndex[vCount + j] = nodeMax + sumAdditionalxCount + j;
            }
            sumAdditionalxCount += vecTimeInvariantDeviceInfo[i].additionalxCount;
        }
    }
    for (int i = 0; i < timeVariantDeviceCount; i++) {
        if (vecTimeVariantDeviceInfo[i].additionalxCount) {
            int vCount = vecTimeVariantDeviceInfo[i].xCount - vecTimeVariantDeviceInfo[i].additionalxCount;
            for (int j = 0; j < vecTimeVariantDeviceInfo[i].additionalxCount; j++) {
                vecTimeVariantDeviceInfo[i].xIndex[vCount + j] = nodeMax + sumAdditionalxCount + j;
            }
            sumAdditionalxCount += vecTimeVariantDeviceInfo[i].additionalxCount;
        }
    }
    for (int i = 0; i < excitationDeviceCount; i++) {
        if (vecExcitationDeviceInfo[i].additionalxCount) {
            int vCount = vecExcitationDeviceInfo[i].xCount - vecExcitationDeviceInfo[i].additionalxCount;
            for (int j = 0; j < vecExcitationDeviceInfo[i].additionalxCount; j++) {
                vecExcitationDeviceInfo[i].xIndex[vCount + j] = nodeMax + sumAdditionalxCount + j;
            }
            sumAdditionalxCount += vecExcitationDeviceInfo[i].additionalxCount;
        }
    }
    nodeCount = nodeMax + 1;//认为0节点为地节点
    matrixDimension = nodeCount + sumAdditionalxCount;
}

Circuit::~Circuit() {
    for (int i = 0; i < timeInvariantDeviceCount; i++) {
        delete vecTimeInvariantDevice[i];
		vecTimeInvariantDevice[i] = nullptr;
    }
    for (int i = 0; i < timeVariantDeviceCount; i++) {
        delete vecTimeVariantDevice[i];
		vecTimeVariantDevice[i] = nullptr;

    }
    for (int i = 0; i < excitationDeviceCount; i++) {
        delete vecExcitationDevice[i];
		vecExcitationDevice[i] = nullptr;
    }
}