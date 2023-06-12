#include "Newton.h"
Newton::Newton(Solver* MySolver) {
	MySolver_ = MySolver;
	Max_Iteration_times = 1000;
}

Newton::~Newton() {
}