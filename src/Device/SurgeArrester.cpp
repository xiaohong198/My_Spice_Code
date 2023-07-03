#include "SurgeArrester.h"
REGISTER(SurgeArrester);

SurgeArrester::SurgeArrester() {
	IVCount = 17;
	IList = new double[IVCount];
	VList = new double[IVCount];
	IDifference = new double[IVCount - 1];
	VDifference = new double[IVCount - 1];
	Coeff0 = new double[IVCount - 1];
	Coeff1 = new double[IVCount - 1];
	Coeff2 = new double[IVCount - 1];
	Coeff3 = new double[IVCount - 1];

	IList[0] = 0;
	IList[1] = 0;
	IList[2] = 0;
	IList[3] = 0;
	IList[4] = 0;
	IList[5] = 0;
	IList[6] = 2.517;
	IList[7] = 12;
	IList[8] = 33.7;
	IList[9] = 102.7;
	IList[10] = 219.5;
	IList[11] = 623.7;
	IList[12] = 1520;
	IList[13] = 2470;
	IList[14] = 3941;
	IList[15] = 4893;
	IList[16] = 5833;

	VList[0] = 0;
	VList[1] = 1;
	VList[2] = 2;
	VList[3] = 3;
	VList[4] = 3.5;
	VList[5] = 4;
	VList[6] = 4.171;
	VList[7] = 4.345;
	VList[8] = 4.448;
	VList[9] = 4.564;
	VList[10] = 4.701;
	VList[11] = 4.906;
	VList[12] = 5.084;
	VList[13] = 5.227;
	VList[14] = 5.373;
	VList[15] = 5.443;
	VList[16] = 5.499;

	fitting(IVCount, IList, VList, IDifference, VDifference, Coeff0, Coeff1, Coeff2, Coeff3);
}
SurgeArrester::~SurgeArrester() {
	delete[]IList;
	delete[]VList;
	delete[]IDifference;
	delete[]VDifference;
	delete[]Coeff0;
	delete[]Coeff1;
	delete[]Coeff2;
	delete[]Coeff3;
}