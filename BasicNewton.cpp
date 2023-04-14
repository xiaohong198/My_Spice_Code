#include "BasicNewton.h"
BasicNewton::BasicNewton(Solver* MySolver): Newton(MySolver) {
}

void BasicNewton::Perform_BaseNewton()
{
	for (int Iteration_times = 0; Iteration_times < Max_Iteration_times; Iteration_times++)
	{
		MySolver_->processJacobianAndF();
		MySolver_->x_Newton = MySolver_->x_Newton - MySolver_->Jacobian.inverse() * MySolver_->F_x0;
		 
		if (((MySolver_->F_x0.cwiseAbs()).maxCoeff() <= Convergence_limit ? true : false)) {
			break;
		}
	}
}

BasicNewton::~BasicNewton() {

}