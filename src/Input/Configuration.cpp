#include <iostream>
#include "Configuration.h"
using namespace std;
Configuration::Configuration() {
}
void Configuration::SetConfiguration() {
	cout << "Input dt = " << endl;
	cin >> dt_;
	cout << "Input T_end = " << endl;
	cin >> t_end_;
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
		dt_method_ = EulerBackward;
		break;
	case 2:
		dt_method_ = Trapezoidal;
		break;
	case 3:
		dt_method_ = BDF_2;
		break;
	case 4:
		dt_method_ = SDC;
		break;
	default:
		break;
	}
}

double Configuration::Getdt() {
	return dt_;
}

double Configuration::GettEnd() {
	return t_end_;
}

TimeDiscretization Configuration::GetTimeDiscretization() {
	return dt_method_;
}

Configuration::~Configuration() {
}