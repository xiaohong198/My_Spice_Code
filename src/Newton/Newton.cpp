#include "Newton.h"
Newton::Newton(Solver* MySolver) {
	MySolver_ = MySolver;
	Max_Iteration_times = 1000;
	Convergence_limit = 1.0e-9;//1.0e-4
}

Newton::~Newton() {

}