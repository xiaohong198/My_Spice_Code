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

	for (auto user_iter = UserParameter_.begin(); user_iter != UserParameter_.end(); user_iter++)
	{
		InputStr user_str = user_iter->second;		
		// 初始化器件类
		Device_ = (Device*)ClassFactory::getInstance().getClassByName(user_str.ClassName);
		Device_->setInputData(user_str, PortCompareMap);
		vecDevice.push_back(Device_);
	}

	for (auto iter_device: vecDevice)
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