#pragma once
#include "TabulatedIVCurveDevice.h"

class SurgeArrester :public TabulatedIVCurveDevice
{
public:
	SurgeArrester();
	~SurgeArrester();

	//  void setIVTable();
};
