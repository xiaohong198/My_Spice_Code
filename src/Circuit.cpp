#include "Circuit.h"
using namespace std;
Circuit::Circuit()
	: Input_(nullptr)
	, Device_(nullptr)
{
	Input_ = new Input();
	Input_->ReadCompareXML();
	Input_->ReadCMD();
	Input_->ReadSCF();

	Input_->InputSCFStrVec;
	Input_->InputCMDStrVec;
	Input_->ComparisonStrVec;

#if 1
	/*-------Mos Level1测试-----*/
	Device_ = new SpiceMosfet();
	Device_->setDeviceInfo_({ 1,2,3,4,5,6 });
	vecDevice.push_back(Device_);

	Device_ = new Vsource_DC();
	Device_->setConstValue(20);
	Device_->setDeviceInfo_({ 1,0,9 });
	vecDevice.push_back(Device_);

	Device_ = new PWLVoltageSource();
	Device_->setDeviceInfo_({ 8,5,10 });
	vecDevice.push_back(Device_);

	Device_ = new Resistor();
	Device_->setConstValue(223.8e-2);
	Device_->setDeviceInfo_({ 3,8 });
	vecDevice.push_back(Device_);

	Device_ = new Resistor();
	Device_->setConstValue(1.5e-3);
	Device_->setDeviceInfo_({ 7,0 });
	vecDevice.push_back(Device_);

	Device_ = new Inductor();
	Device_->setConstValue(1.0e-9);
	Device_->setDeviceInfo_({ 5,7,11 });
	vecDevice.push_back(Device_);

	SetClassVec();

	nodeCount = 9;
	AdditaionalxCount = 3;
	matrixDimension = nodeCount + AdditaionalxCount;

#endif // 0
}

Circuit::~Circuit() {

}

void Circuit::SetClassVec()
{
	for (auto iter: vecDevice)
	{
		// 获得类型值
		int re_prime = iter->getReturnPrime();
	
		if ((re_prime & PrimeA) == PrimeA)
		{
			vecDeviceForMatrixA.push_back(iter);
		}
		if ((re_prime & PrimeB) == PrimeB)
		{
			vecDeviceForMatrixB.push_back(iter);
		}
		if ((re_prime & PrimeP) == PrimeP)
		{
			vecDeviceForMatrixP.push_back(iter);
		}
		if ((re_prime & PrimeQ) == PrimeQ)
		{
			vecDeviceForMatrixQ.push_back(iter);
		}
		if ((re_prime & PrimeC) == PrimeC)
		{
			vecDeviceForMatrixC.push_back(iter);
		}
		if ((re_prime & PrimeE) == PrimeE)
		{
			vecDeviceForVectorE.push_back(iter);
		}
	}
}
