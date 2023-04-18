#include <iostream>
#include "Configuration.h"
using namespace std;
Configuration::Configuration() {
	dt = 0.01;
	t_end = 1;
	dt_method = EulerBackward;
}
void Configuration::Set_Configuration() {
	cout << "Input dt = " << endl;
	cin >> dt;
	cout << "Input T_end = " << endl;
	cin >> t_end;
	cout << "Choose time discretization method: " << endl;
	cout << "'1' for EulerBackward" << endl;
	cout << "'2' for TrapezoidalIntegration" << endl;
	cout << "'3' for BDF-2" << endl;
	cout << "'4' for SDC" << endl;
	int Mychoice;
	cin >> Mychoice;
	switch (Mychoice)
	{
	case 1:
		dt_method = EulerBackward;
		break;
	case 2:
		dt_method = Trapezoidal;
		break;
	case 3:
		dt_method = BDF_2;
		break;
	case 4:
		dt_method = SDC;
		break;
	default:
		//cout << "Error! Choose EulerBackward then!" << endl;
		break;
	}
}

double Configuration::Get_dt() {
	return dt;
}

double Configuration::Get_t_end() {
	return t_end;
}

TimeDiscretization Configuration::Get_TimeDiscretization() {
	return dt_method;
}

Configuration::~Configuration() {

}