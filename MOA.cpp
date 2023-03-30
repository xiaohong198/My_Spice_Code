#include "MOA.h"
#include <iostream>
using namespace std;

MOA::MOA() {
	IVCount = 11;
	IList = new double[IVCount];
	VList = new double[IVCount];
	IDifference = new double[IVCount - 1];
	VDifference = new double[IVCount - 1];
	Coeff0 = new double[IVCount - 1];
	Coeff1 = new double[IVCount - 1];
	Coeff2 = new double[IVCount - 1];
	Coeff3 = new double[IVCount - 1];

	IList[0] = 0.001;
	IList[1] = 0.01;
	IList[2] = 0.1;
	IList[3] = 0.2;
	IList[4] = 0.38;
	IList[5] = 0.65;
	IList[6] = 1.11;
	IList[7] = 1.5;
	IList[8] = 2;
	IList[9] = 2.8;
	IList[10] = 200;

	VList[0] = 1.1;
	VList[1] = 1.6;
	VList[2] = 1.7;
	VList[3] = 1.739;
	VList[4] = 1.777;
	VList[5] = 1.815;
	VList[6] = 1.853;
	VList[7] = 1.881;
	VList[8] = 1.91;
	VList[9] = 1.948;
	VList[10] = 3.2;

	fitting(IVCount, IList, VList, IDifference, VDifference, Coeff0, Coeff1, Coeff2, Coeff3);
}
MOA::~MOA() {
	delete[]IList;
	delete[]VList;
	delete[]IDifference;
	delete[]VDifference;
	delete[]Coeff0;
	delete[]Coeff1;
	delete[]Coeff2;
	delete[]Coeff3;
}