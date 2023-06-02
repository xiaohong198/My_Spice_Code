#include "Circuit.h"
Circuit::Circuit()
	: Input_(nullptr)
	, Device_(nullptr)
{
	Input_ = new Input();
	UserParameter_ = Input_->GetParameter();
	PortCompareMap = Input_->GetPortCompare();
	HintCompareMap = Input_->GetHintCompare();

	for (auto user_iter = UserParameter_.begin(); user_iter != UserParameter_.end(); user_iter++)
	{
		string instance_name = user_iter->first;
		InputStr user_str = user_iter->second;		
		// 初始化器件类
		Device_ = (Device*)ClassFactory::getInstance().getClassByName(user_str.ClassName);
		Device_->setInputData(user_str, PortCompareMap);
		vecDevice.push_back(Device_);
	}

	for (auto iter_device: vecDevice)
	{
		iter_device->setDeviceInfo(PortCompareMap);
		DeviceInfoStr info = iter_device->getDeviceInfo();
	}
	SetClassVec();
	nodeCount = 9;
	AdditaionalxCount = 3;
	matrixDimension = nodeCount + AdditaionalxCount;
}

Circuit::~Circuit() {

}

void Circuit::SetClassVec()
{
	const int primes[] = { PrimeA, PrimeB, PrimeP, PrimeQ, PrimeC, PrimeE };
	vector<Device*>* matrixes[] = { &vecDeviceForMatrixA, &vecDeviceForMatrixB, &vecDeviceForMatrixP, &vecDeviceForMatrixQ, &vecDeviceForMatrixC, &vecDeviceForVectorE };

	for (auto iter : vecDevice)
	{
		int re_prime = iter->getReturnPrime();
		for (int i = 0; i < sizeof(primes) / sizeof(int); i++)
		{
			if ((re_prime & primes[i]) == primes[i])
			{
				matrixes[i]->push_back(iter);
			}
		}
	}
}
