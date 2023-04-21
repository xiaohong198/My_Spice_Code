#pragma once
#include "Device.h"
#include <vector>
using namespace std;

class Circuit;
class structDeviceInfo {
    friend class Circuit;
private:
    char deviceType;
    int  deviceIndexPerClass;
    int   xCount;//未知量的个数
    int* xIndex;//未知量的位置
    int additionalxCount;//额外变量的个数
public:
    structDeviceInfo();
    ~structDeviceInfo();

    int* getxIndex();
    int getXCount();
};

