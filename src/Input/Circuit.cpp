#include "Circuit.h"

Circuit::Circuit()
	: input_(nullptr)
	, device_(nullptr)
{
	const int primes[] = { kPrimeA, kPrimeB, kPrimeP, kPrimeQ, kPrimeC, kPrimeE };
	vector<Device*>* matrixes[] = { &device_matrix_a_, &device_matrix_b_, &device_matrix_p_, &device_matrix_q_, &device_matrix_c_, &device_matrix_e_ };
	vector <Device*> vecDevice;
	input_ = new Input();
	user_compare_ = input_->GetParameter();
	port_compare_ = input_->GetPortCompare();
	hint_compare_ = input_->GetHintCompare();
	plot_compare_ = input_->GetPlotCompare();

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

	for (auto user_iter = user_compare_.begin(); user_iter != user_compare_.end(); user_iter++)
	{
		InputStr user_str = user_iter->second;
		// 初始化器件类
		device_ = (Device*)ClassFactory::GetInstance().GetClassByName(user_str.class_name);
		device_->SetInputData(user_str, port_compare_);
		vecDevice.push_back(device_);
		//填充实例名和端口号顺序的映射表
		device_port_compare_.insert({ user_str.instance_name,user_str.port });
	}

	for (auto iter_device : vecDevice)
	{
		iter_device->voltage_x_index_ = voltage_x_index_;
		iter_device->current_x_index_ = current_x_index_;
		iter_device->SetDeviceInfo(port_compare_);
		voltage_x_index_ = iter_device->voltage_x_index_;
		current_x_index_ = iter_device->current_x_index_;
		//填充实例名和新增IV的映射表
		device_additional_compare_.insert({ iter_device->GetInstanceName(), iter_device->GetDeviceInfo().additional_index });
		//判断ABCPQE
		int re_prime = iter_device->GetReturnPrime();
		for (int i = 0; i < sizeof(primes) / sizeof(int); i++)
		{
			if ((re_prime & primes[i]) == primes[i])
			{
				matrixes[i]->push_back(iter_device);
			}
		}
	}
	matrix_dimension_ = voltage_x_index_.size() + current_x_index_.size();
}

Circuit::~Circuit() {
}