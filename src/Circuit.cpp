#include "Circuit.h"
using namespace std;
Circuit::Circuit() 
	: Input_(nullptr)
	, Device_(nullptr)
{

	Input_ = new Input();
	Input_->ReadSCF();
	Input_->ReadCMD();
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

}

void Circuit::SetClassVec()
{
	for (auto iter: vecDevice)
	{
		// 获得类型值
		int re_prime = iter->getReturnPrime();
		// 获取质数构成
		vector<int> factors;
		//质数组成
		if (re_prime % 2 == 0)
		{
			factors.push_back(2);
			re_prime = re_prime / 2;
		}
		for (int i = 3; i <= sqrt(re_prime); i = i + 2)
		{
			if (re_prime % i == 0)
			{
				factors.push_back(i);
				re_prime = re_prime / i;
			}
		}
		if (re_prime > 2)
			factors.push_back(re_prime);
		//判断质数类别
		for (auto factors_iter: factors)
		{
			if (factors_iter == PrimeA)
			{
				vecDeviceForMatrixA.push_back(iter);
			}
			if (factors_iter == PrimeB)
			{
				vecDeviceForMatrixB.push_back(iter);
			}
			if (factors_iter == PrimeP)
			{
				vecDeviceForMatrixP.push_back(iter);
			}
			if (factors_iter == PrimeQ)
			{
				vecDeviceForMatrixQ.push_back(iter);
			}
			if (factors_iter == PrimeC)
			{
				vecDeviceForMatrixC.push_back(iter);
			}
			if (factors_iter == PrimeE)
			{
				vecDeviceForVectorE.push_back(iter);
			}
		}
	}

}
