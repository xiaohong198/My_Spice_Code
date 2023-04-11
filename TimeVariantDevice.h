#pragma once
#include "Device.h"

enum modelType { exponentialModel, macroModel };

class TimeVariantDevice :public Device
{
public:
	TimeVariantDevice();
	~TimeVariantDevice();

	//virtual double f(double)=0;
	//virtual double G(double)=0;
};

