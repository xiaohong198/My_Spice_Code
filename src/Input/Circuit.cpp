#include "Circuit.h"

Circuit::Circuit()
	: Input_(nullptr)
	, Device_(nullptr)
{
	const int primes[] = { PrimeA, PrimeB, PrimeP, PrimeQ, PrimeC, PrimeE };
	vector<Device*>* matrixes[] = { &vecDeviceForMatrixA, &vecDeviceForMatrixB, &vecDeviceForMatrixP, &vecDeviceForMatrixQ, &vecDeviceForMatrixC, &vecDeviceForVectorE };
	vector <Device*> vecDevice;
	Input_ = new Input();
	UserParameter_ = Input_->GetParameter();
	PortCompareMap = Input_->GetPortCompare();
	HintCompareMap = Input_->GetHintCompare();

#if 0
	/*-------Mos Level1 BS短路 测试-----*/
	//Device_ = new SpiceMosfet();
	//Device_->setDeviceInfo_({ 1,2,3,4,4,5 });
	//vecDevice.push_back(Device_);

	//Device_ = new Vsource_DC();
	//Device_->setConstValue(20);
	//Device_->setDeviceInfo_({ 1,0,8 });
	//vecDevice.push_back(Device_);

	//Device_ = new PWLVoltageSource();
	//Device_->setDeviceInfo_({ 7,4,9 });
	//vecDevice.push_back(Device_);

	//Device_ = new Resistor();
	//Device_->setConstValue(223.8e-2);
	//Device_->setDeviceInfo_({ 3,7 });
	//vecDevice.push_back(Device_);

	//Device_ = new Resistor();
	//Device_->setConstValue(1.5e-3);
	//Device_->setDeviceInfo_({ 6,0 });
	//vecDevice.push_back(Device_);

	//Device_ = new Inductor();
	//Device_->setConstValue(1.0e-9);
	//Device_->setDeviceInfo_({ 4,6,10 });
	//vecDevice.push_back(Device_);

	//SetClassVec();

	//ReadVoltageXIndex = { 0,1,2,3,4,5,6,7 };
	//ReadCurrentXIndex = { 8,9,10};
	//matrixDimension = ReadVoltageXIndex.size() + ReadCurrentXIndex.size();

	/*-------Mos Level1暂态测试-----*/
//	Device_ = new PWLVoltageSource();
//	Device_->setDeviceInfo_({ 2,1,8 });
//	vecDevice.push_back(Device_);
//
//	Device_ = new Resistor();
//	Device_->setConstValue(8.5);
//	Device_->setDeviceInfo_({ 2,3 });
//	vecDevice.push_back(Device_);
//
//	Device_ = new SpiceMosfet();
//	Device_->setDeviceInfo_({ 4,12,3,5,5,13 });
//	vecDevice.push_back(Device_);
//
//	//Device_ = new SpiceDiode();
//	//Device_->setDeviceInfo_({ 5,14,4 });
//	//vecDevice.push_back(Device_);
//	Device_ = new Diode();
//	Device_->setDeviceInfo_({ 5,4 });
//	vecDevice.push_back(Device_);
//
//	Device_ = new Capacitor();
//	Device_->setConstValue(13e-12);
//	Device_->setDeviceInfo_({ 3,4 });
//	vecDevice.push_back(Device_);
//
//	Device_ = new Inductor();
//	Device_->setConstValue(7.5e-10);
//	Device_->setDeviceInfo_({ 5,1,10 });
//	vecDevice.push_back(Device_);
//
//	Device_ = new Inductor();
//	Device_->setConstValue(63.5e-11);
//	Device_->setDeviceInfo_({ 1,0,11 });
//	vecDevice.push_back(Device_);
//
//	Device_ = new Capacitor();
//	Device_->setConstValue(14e-12);
//	Device_->setDeviceInfo_({ 6,4 });
//	vecDevice.push_back(Device_);
//
//	//Device_ = new SpiceDiode();
//	//Device_->setDeviceInfo_({ 4,15,6 });
//	//vecDevice.push_back(Device_);
//	Device_ = new Diode();
//	Device_->setDeviceInfo_({ 4,6 });
//	vecDevice.push_back(Device_);
//
//	Device_ = new Jsource_DC();
//	Device_->setConstValue(20);
//	Device_->setDeviceInfo_({ 6,4 });
//	vecDevice.push_back(Device_);
//
//	Device_ = new Resistor();
//	Device_->setConstValue(47e-3);
//	Device_->setDeviceInfo_({ 6,7 });
//	vecDevice.push_back(Device_);
//
//	Device_ = new Vsource_DC();
//	Device_->setConstValue(50);
//	Device_->setDeviceInfo_({ 7,0,9 });
//	vecDevice.push_back(Device_);
//
//	SetClassVec();
//
////	ReadVoltageXIndex = { 0,1,2,3,4,5,6,7,12,13,14,15 };
//	ReadVoltageXIndex = { 0,1,2,3,4,5,6,7,12,13 };
//	ReadCurrentXIndex = { 8,9,10,11 };
//	matrixDimension = ReadVoltageXIndex.size() + ReadCurrentXIndex.size();

	/*------R L Voltage-----*/
	//Device_ = new Resistor();
	//Device_->setConstValue(10);
	//Device_->setDeviceInfo_({ 2,0 });
	//vecDevice.push_back(Device_);

	//Device_ = new SpiceDiode();
	//Device_->setDeviceInfo_({ 1,1,2 });
	//vecDevice.push_back(Device_);

	//Device_ = new Vsource_AC();
	//Device_->setDeviceInfo_({ 1,0,3 });
	//vecDevice.push_back(Device_);

	//SetClassVec();

	//ReadVoltageXIndex = { 0,1,2};
	//ReadCurrentXIndex = { 3 };
	//matrixDimension = ReadVoltageXIndex.size() + ReadCurrentXIndex.size();

	/*------Mos1 paper debug1-----*/
	//Device_ = new PWLVoltageSource();
	//Device_->setDeviceInfo_({ 2,1,8 });
	//vecDevice.push_back(Device_);

	//Device_ = new Resistor();
	//Device_->setConstValue(8.5);
	//Device_->setDeviceInfo_({ 2,3 });
	//vecDevice.push_back(Device_);
	//
	//Device_ = new SpiceMosfet();
	//Device_->setDeviceInfo_({ 4,12,3,14,5,13 });
	//vecDevice.push_back(Device_);

	//Device_ = new SpiceDiode();
	//Device_->setDeviceInfo_({ 5,15,4 });
	//vecDevice.push_back(Device_);

	//Device_ = new Capacitor();
	//Device_->setConstValue(13e-12);
	//Device_->setDeviceInfo_({ 3,4 });
	//vecDevice.push_back(Device_);

	//Device_ = new Inductor();
	//Device_->setConstValue(7.5e-10);
	//Device_->setDeviceInfo_({ 5,1,10 });
	//vecDevice.push_back(Device_);

	//Device_ = new Inductor();
	//Device_->setConstValue(63.5e-11);
	//Device_->setDeviceInfo_({ 1,0,11 });
	//vecDevice.push_back(Device_);

	//Device_ = new Capacitor();
	//Device_->setConstValue(14e-12);
	//Device_->setDeviceInfo_({ 6,4 });
	//vecDevice.push_back(Device_);

	//Device_ = new SpiceDiode();
	//Device_->setDeviceInfo_({ 4,16,6 });
	//vecDevice.push_back(Device_);

	//Device_ = new Jsource_DC();
	//Device_->setConstValue(20);
	//Device_->setDeviceInfo_({ 6,4 });
	//vecDevice.push_back(Device_);

	//Device_ = new Resistor();
	//Device_->setConstValue(47e-3);
	//Device_->setDeviceInfo_({ 6,7 });
	//vecDevice.push_back(Device_);

	//Device_ = new Vsource_DC();
	//Device_->setConstValue(50);
	//Device_->setDeviceInfo_({ 7,0,9 });
	//vecDevice.push_back(Device_);

	//SetClassVec();

	//ReadVoltageXIndex = { 0,1,2,3,4,5,6,7,12,13,14,15,16 };
	//ReadCurrentXIndex = { 8,9,10,11 };
	//matrixDimension = ReadVoltageXIndex.size() + ReadCurrentXIndex.size();

	/*---Mos1 paper debug2----*/
	Device_ = new PWLVoltageSource();
	Device_->setDeviceInfo_({ 2,1,8 });
	vecDevice.push_back(Device_);

	Device_ = new Resistor();
	Device_->setConstValue(8.5);
	Device_->setDeviceInfo_({ 2,3 });
	vecDevice.push_back(Device_);

	Device_ = new SpiceMosfet();
	Device_->setDeviceInfo_({ 4,12,3,14,5,13 });
	vecDevice.push_back(Device_);

	Device_ = new Diode();
	Device_->setDeviceInfo_({ 5,4 });
	vecDevice.push_back(Device_);

	Device_ = new Capacitor();
	Device_->setConstValue(13e-12);
	Device_->setDeviceInfo_({ 3,4 });
	vecDevice.push_back(Device_);

	Device_ = new Inductor();
	Device_->setConstValue(7.5e-10);
	Device_->setDeviceInfo_({ 5,1,10 });
	vecDevice.push_back(Device_);

	Device_ = new Inductor();
	Device_->setConstValue(63.5e-11);
	Device_->setDeviceInfo_({ 1,0,11 });
	vecDevice.push_back(Device_);

	Device_ = new Capacitor();
	Device_->setConstValue(14e-12);
	Device_->setDeviceInfo_({ 6,4 });
	vecDevice.push_back(Device_);

	Device_ = new Diode();
	Device_->setDeviceInfo_({ 4,6 });
	vecDevice.push_back(Device_);

	Device_ = new Jsource_DC();
	Device_->setConstValue(20);
	Device_->setDeviceInfo_({ 6,4 });
	vecDevice.push_back(Device_);

	Device_ = new Resistor();
	Device_->setConstValue(47e-3);
	Device_->setDeviceInfo_({ 6,7 });
	vecDevice.push_back(Device_);

	Device_ = new Vsource_DC();
	Device_->setConstValue(50);
	Device_->setDeviceInfo_({ 7,0,9 });
	vecDevice.push_back(Device_);

	SetClassVec();

	ReadVoltageXIndex = { 0,1,2,3,4,5,6,7,12,13,14 };
	ReadCurrentXIndex = { 8,9,10,11 };
	matrixDimension = ReadVoltageXIndex.size() + ReadCurrentXIndex.size();

	/*---Mos1 paper debug3----*/
	//Device_ = new PWLVoltageSource();
	//Device_->setDeviceInfo_({ 2,1,7 });
	//vecDevice.push_back(Device_);

	//Device_ = new Resistor();
	//Device_->setConstValue(8.5);
	//Device_->setDeviceInfo_({ 2,3 });
	//vecDevice.push_back(Device_);

	//Device_ = new SpiceMosfet();
	//Device_->setDeviceInfo_({ 4,11,3,13,5,12 });
	//vecDevice.push_back(Device_);

	//Device_ = new Capacitor();
	//Device_->setConstValue(13e-12);
	//Device_->setDeviceInfo_({ 3,4 });
	//vecDevice.push_back(Device_);

	//Device_ = new Inductor();
	//Device_->setConstValue(7.5e-10);
	//Device_->setDeviceInfo_({ 5,1,9 });
	//vecDevice.push_back(Device_);

	//Device_ = new Inductor();
	//Device_->setConstValue(63.5e-11);
	//Device_->setDeviceInfo_({ 1,0,10 });
	//vecDevice.push_back(Device_);

	//Device_ = new Resistor();
	//Device_->setConstValue(47e-3);
	//Device_->setDeviceInfo_({ 4,6 });
	//vecDevice.push_back(Device_);

	//Device_ = new Vsource_DC();
	//Device_->setConstValue(50);
	//Device_->setDeviceInfo_({ 6,0,8 });
	//vecDevice.push_back(Device_);

	//SetClassVec();

	//ReadVoltageXIndex = { 0,1,2,3,4,5,6,11,12,13 };
	//ReadCurrentXIndex = { 7,8,9,10};
	//matrixDimension = ReadVoltageXIndex.size() + ReadCurrentXIndex.size();

#endif // 0

	for (auto user_iter = UserParameter_.begin(); user_iter != UserParameter_.end(); user_iter++)
	{
		InputStr user_str = user_iter->second;
		// 初始化器件类
		Device_ = (Device*)ClassFactory::getInstance().getClassByName(user_str.ClassName);
		Device_->setInputData(user_str, PortCompareMap);
		vecDevice.push_back(Device_);
	}

	for (auto iter_device : vecDevice)
	{
		iter_device->VoltageXIndex = VoltageXIndex;
		iter_device->CurrentXIndex = CurrentXIndex;
		iter_device->setDeviceInfo(PortCompareMap);
		VoltageXIndex = iter_device->VoltageXIndex;
		CurrentXIndex = iter_device->CurrentXIndex;

		int re_prime = iter_device->getReturnPrime();
		for (int i = 0; i < sizeof(primes) / sizeof(int); i++)
		{
			if ((re_prime & primes[i]) == primes[i])
			{
				matrixes[i]->push_back(iter_device);
			}
		}
	}
	matrixDimension = VoltageXIndex.size() + CurrentXIndex.size();
}

Circuit::~Circuit() {
}