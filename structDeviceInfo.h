#pragma once
#include "Device.h"
#include <vector>
using namespace std;

//struct DeviceInfoStr
//{
//	char deviceType;
//	int  deviceIndexPerClass;
//	int  xCount;//δ֪���ĸ���
//	int* xIndex;//δ֪����λ��
//	int  additionalxCount;//��������ĸ���
//};

class Circuit;
class structDeviceInfo {
    friend class Circuit;
private:
    //char deviceType;
    //int  deviceIndexPerClass;
    //int   xCount;//δ֪���ĸ���
    //int* xIndex;//δ֪����λ��
    //int additionalxCount;//��������ĸ���
public:
    structDeviceInfo();
    ~structDeviceInfo();

    //int* getxIndex();
    //int getXCount();
};

