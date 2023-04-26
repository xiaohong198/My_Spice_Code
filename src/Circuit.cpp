#include "Circuit.h"
using namespace std;
Circuit::Circuit() 
	: Input_(nullptr)
	, Device_(nullptr)
{

	Input_ = new Input();
	Input_->ReadSCF();
	Input_->GetInput(input_vec_);

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

#if 1
	/*-------Mos Level1测试-----*/
	Device_ = new SpiceMosfet();
	vecTimeVariantDevice.push_back(Device_);
	vecDevice.push_back(Device_);
	DeviceInfo_.xIndex = { 1,2,3,4,5,6 };
	vecTimeVariantDeviceInfo.push_back(DeviceInfo_);
	vecDeviceInfo.push_back(DeviceInfo_);

	vecDeviceForMatrixA;
	
	Device_ = new Vsource_DC();
	Device_->setConstValue(20);
	vecExcitationDevice.push_back(Device_);
	vecDevice.push_back(Device_);
	DeviceInfo_.xIndex = { 1,0,9 };
	vecExcitationDeviceInfo.push_back(DeviceInfo_);
	vecDeviceInfo.push_back(DeviceInfo_);


	Device_ = new PWLVoltageSource();
	vecExcitationDevice.push_back(Device_);
	vecDevice.push_back(Device_);
	DeviceInfo_.xIndex = { 8,5,10 };
	vecExcitationDeviceInfo.push_back(DeviceInfo_);
	vecDeviceInfo.push_back(DeviceInfo_);

	Device_ = new Resistor();
	Device_->setConstValue(223.8e-2);
	vecDevice.push_back(Device_);
	DeviceInfo_.xIndex = { 3,8 };
	vecDeviceInfo.push_back(DeviceInfo_);

	Device_ = new Resistor();
	Device_->setConstValue(1.5e-3);
	vecDevice.push_back(Device_);
	DeviceInfo_.xIndex = { 7,0 };
	vecDeviceInfo.push_back(DeviceInfo_);

	Device_ = new Inductor();
	Device_->setConstValue(1.0e-9);
	vecDevice.push_back(Device_);
	DeviceInfo_.xIndex = { 5,7,11 };
	vecDeviceInfo.push_back(DeviceInfo_);

	//timeInvariantDeviceCount = vecTimeInvariantDevice.size();
	DeviceCount = vecDevice.size();
	timeVariantDeviceCount = vecTimeVariantDevice.size();
	excitationDeviceCount = vecExcitationDevice.size();
	nodeCount = 9;
	AdditaionalxCount = 3;
	matrixDimension = nodeCount + AdditaionalxCount;

#endif // 0

    /*----------SpiceDiode测试---------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 5;

    //vecTimeVariantDevice.push_back(new SpiceDiode());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeVariantDeviceInfo[0]->deviceType = 'D';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 3;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[2] = 3;

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

    /*-----测试coding功能---*/
    //cout << endl;
}

Circuit::~Circuit() {
    for (int i = 0; i < DeviceCount; i++) {
        delete vecDevice[i];
    }
    for (int i = 0; i < timeVariantDeviceCount; i++) {
        delete vecTimeVariantDevice[i];
    }
    for (int i = 0; i < excitationDeviceCount; i++) {
        delete vecExcitationDevice[i];
    }
}