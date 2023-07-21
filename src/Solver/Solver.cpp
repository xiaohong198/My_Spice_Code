#include "Solver.h"
Solver::Solver(Configuration* _my_config, Circuit* _my_circuit) {
	my_config_ = _my_config;
	my_circuit_ = _my_circuit;
	output_ = new Output();
	size_ = my_circuit_->matrix_dimension_;
	voltage_x_index_ = my_circuit_->voltage_x_index_;
	current_x_index_ = my_circuit_->current_x_index_;
	/*---------------------矩阵初始�?--------------------*/
	A_ = Eigen::MatrixXd::Zero(size_, size_);

	B_ = Eigen::MatrixXd::Zero(size_, size_);

	P_Jacobian_ = Eigen::MatrixXd::Zero(size_, size_);

	Q_Jacobian_ = Eigen::MatrixXd::Zero(size_, size_);

	//E = Eigen::VectorXd::Zero(size);
	E_Integral_ = Eigen::VectorXd::Zero(size_);

	P_ = Eigen::VectorXd::Zero(size_);

	P_s1_ = Eigen::VectorXd::Zero(size_);

	Q_ = Eigen::VectorXd::Zero(size_);
	Q_s1_ = Eigen::VectorXd::Zero(size_);
	Q_s2_ = Eigen::VectorXd::Zero(size_);

	C_ = Eigen::MatrixXd::Zero(size_, size_);
	C_s1_ = Eigen::MatrixXd::Zero(size_, size_);
	C_s2_ = Eigen::MatrixXd::Zero(size_, size_);

	x_ = Eigen::VectorXd::Zero(size_);
	x_s2_ = Eigen::VectorXd::Zero(size_);
	x_newton_ = Eigen::VectorXd::Zero(size_);
	F_x0_ = Eigen::VectorXd::Zero(size_);
	Jacobian_ = Eigen::MatrixXd::Zero(size_, size_);

	dt_ = my_config_->Getdt();
	t_end_ = my_config_->GettEnd();

	/*--------------------------------------------------*/
	/*-----mos1 paper-----*/
	//for (int i = 0; i < size; i++) {
	//	x(i) = 0;
	//}
	//x(1) = 52;
	//x(2) = 50;
	//x(3) = 48;
	//x(4) = 48;
	//x(5) = 50;
	//x(6) = 48;
	//x(7) = 50;
	//x(12) = x(4);
	//x(13) = x(5);

	/*-----mos1 debug2-----*/
	//for (int i = 0; i < size; i++) {
	//	x(i) = 0;
	//}
	//x(1) = 52;//n1
	//x(6) = 50;//n2
	//x(4) = 50;//n3
	//x(3) = 50;//n4
	//x(2) = 50;//n5
	//x(7) = 50;//n6
	//x(8) = 50;//n7
	//
	//x(11) = x(3);//n12_Dp = D
	//x(12) = x(2);//n13_Sp = S
	//x(5) = 50;//n14

	/*----mos1 debug3---*/
	//for (int i = 0; i < size; i++) {
	//	x(i) = 0;
	//}
	//x(1) = 52;
	//x(2) = 50;
	//x(3) = 50;
	//x(4) = 50;
	//x(5) = 50;
	//x(6) = 50;
	//x(7) = 50;
	//x(12) = x(4);
	//x(13) = x(5);
	//x(14) = 50;
	//x(15) = x(5);
	//x(16) = x(4);

	/*-----mos1 debug2-----*/
	for (int i = 0; i < size_; i++) {
		x_(i) = 0;
	}
	map<string, int> hint_map = my_circuit_->hint_compare_;
	for (auto hint_index = hint_map.begin(); hint_index != hint_map.end(); hint_index++)
	{
		string port = hint_index->first;
		int port_value = hint_index->second;

		x_(my_circuit_->port_compare_[port]) = port_value;
		//判断SpiceDevice
		for (auto additional_index = my_circuit_->device_additional_compare_.begin(); additional_index != my_circuit_->device_additional_compare_.end(); additional_index++)
		{
			string instance_name = additional_index->first;
			vector<int> additional_vec = additional_index->second;
			//是特殊器件
			if (additional_vec.size() == 2)
			{
				//特殊器件端口号列表n0 n1 n2
				vector<string> port_vec = my_circuit_->device_port_compare_[instance_name];
				//特殊器件第一个和第三个端口号的值分别赋值给这个特殊器件自增的第一个和第二个值
				x_(additional_vec[0]) = x_(my_circuit_->port_compare_[port_vec[0]]);
				x_(additional_vec[1]) = x_(my_circuit_->port_compare_[port_vec[2]]);
			}
		}
	}
	//x(5) = 52;//n1=52
	//x(7) = 50;//n2=50
	//x(3) = 50;//n3=50
	//x(2) = 50;//n4=50
	//x(4) = 50;//n5=50
	//x(1) = 50;//n6=50
	//x(8) = 50;//n7=50
	//x(13) = 0;//n8_ipwl
	//x(14) = 0;//n9_idc
	//x(10) = 0;//n10_iLs
	//x(9) = 0;//n11_iLd
	//x(11) = x(3);//n12_Dp = D
	//x(12) = x(2);//n13_Sp = S
	//x(6) = 50;//n14=50
	x_s2_ = x_;
	x_newton_ = x_;

	Solver::x_result_vec_.push_back(Solver::x_);
	Solver::time_result_vec_.push_back(0);

	ProcessA();//A、B只填一次就不动�?

	ProcessB();//A、B只填一次就不动�?
}

void Solver::ProcessA() {//扫描所有器�?
	for (auto iter : my_circuit_->device_matrix_a_) {
		DeviceInfoStr current_info = iter->GetDeviceInfo();
		vector<int> index = current_info.x_index;
		int x_count_temp = index.size();
		Eigen::MatrixXd subA = Eigen::MatrixXd::Zero(x_count_temp, x_count_temp);
		iter->GetSubA(subA);
		for (int i = 0; i < x_count_temp; i++) {
			for (int j = 0; j < x_count_temp; j++) {
				int row_num = index[i];
				int col_num = index[j];
				A_(row_num, col_num) += subA(i, j);
			}
		}
	}
}

void Solver::ProcessB() {
	for (auto iter : my_circuit_->device_matrix_b_) {
		DeviceInfoStr current_info = iter->GetDeviceInfo();
		vector<int> index = current_info.x_index;
		int x_count_temp = index.size();
		Eigen::MatrixXd subB = Eigen::MatrixXd::Zero(x_count_temp, x_count_temp);
		iter->GetSubB(subB);
		for (int i = 0; i < x_count_temp; i++) {
			for (int j = 0; j < x_count_temp; j++) {
				int row_num = index[i];
				int col_num = index[j];
				B_(row_num, col_num) += subB(i, j);
			}
		}
	}
}

void Solver::ProcessEIntegral(double* tList) {
	for (auto iter : my_circuit_->device_matrix_e_) {
		DeviceInfoStr current_info = iter->GetDeviceInfo();
		vector<int> index = current_info.x_index;
		int x_count_temp = index.size();
		Eigen::VectorXd subEIntegral = Eigen::VectorXd::Zero(x_count_temp);
		iter->GetSubEIntegral(subEIntegral, tList);
		for (int i = 0; i < x_count_temp; i++) {
			int row_num = index[i];
			E_Integral_(row_num) += subEIntegral(i);
		}
	}
}

void Solver::ProcessP() {
	for (auto iter : my_circuit_->device_matrix_p_) {
		DeviceInfoStr current_info = iter->GetDeviceInfo();
		vector<int> index = current_info.x_index;
		int x_count_temp = index.size();
		Eigen::MatrixXd subPJacobian = Eigen::MatrixXd::Zero(x_count_temp, x_count_temp);
		Eigen::VectorXd subP = Eigen::VectorXd::Zero(x_count_temp);
		Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(x_count_temp);
		for (int i = 0; i < x_count_temp; i++) {
			int row_num = index[i];

			nodeValue(i) = x_newton_(row_num);
		}
		iter->GetSubPandPJacobian(nodeValue, subP, subPJacobian);
		for (int i = 0; i < x_count_temp; i++) {
			int row_num = index[i];
			P_(row_num) += subP(i);
			for (int j = 0; j < x_count_temp; j++) {
				int col_num = index[j];
				P_Jacobian_(row_num, col_num) += subPJacobian(i, j);
			}
		}
	}
}

void Solver::ProcessQ() {
	for (auto iter : my_circuit_->device_matrix_q_) {
		DeviceInfoStr current_info = iter->GetDeviceInfo();
		vector<int> index = current_info.x_index;
		int x_count_temp = index.size();
		Eigen::MatrixXd subQJacobian = Eigen::MatrixXd::Zero(x_count_temp, x_count_temp);
		Eigen::VectorXd subQ = Eigen::VectorXd::Zero(x_count_temp);
		Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(x_count_temp);
		for (int i = 0; i < x_count_temp; i++) {
			int row_num = index[i];

			nodeValue(i) = x_newton_(row_num);
		}
		iter->GetSubQandQJacobian(nodeValue, subQ, subQJacobian);
		for (int i = 0; i < x_count_temp; i++) {
			int row_num = index[i];
			Q_(row_num) += subQ(i);
			for (int j = 0; j < x_count_temp; j++) {
				int col_num = index[j];
				Q_Jacobian_(row_num, col_num) += subQJacobian(i, j);
			}
		}
	}
}

void Solver::ProcessC() {
	for (auto iter : my_circuit_->device_matrix_c_) {
		DeviceInfoStr current_info = iter->GetDeviceInfo();
		vector<int> index = current_info.x_index;
		int x_count_temp = index.size();
		Eigen::MatrixXd subC = Eigen::MatrixXd::Zero(x_count_temp, x_count_temp);
		Eigen::VectorXd nodeValue = Eigen::VectorXd::Zero(x_count_temp);
		for (int i = 0; i < x_count_temp; i++) {
			int row_num = index[i];

			nodeValue(i) = x_newton_(row_num);
		}
		iter->GetSubC(nodeValue, subC);
		for (int i = 0; i < x_count_temp; i++) {
			int row_num = index[i];
			for (int j = 0; j < x_count_temp; j++) {
				int col_num = index[j];
				C_(row_num, col_num) += subC(i, j);
			}
		}
	}
}

void Solver::ProcessGroundedNodeEqu() {//���񻹿��Ծ��򣿰�A B Eժ��ȥ��
	A_.row(0).setZero();
	A_(0, 0) = 1;
	B_.row(0).setZero();
	P_Jacobian_.row(0).setZero();
	Q_Jacobian_.row(0).setZero();
	C_.row(0).setZero();
	//C_s1.row(0).setZero();
	E_Integral_.row(0).setZero();
	P_.row(0).setZero();
	//P_s1.row(0).setZero();
	//if (P_s1.size() != 0) {
	//    P_s1.row(0).setZero();
	//}
	Q_.row(0).setZero();
	//Q_s1.row(0).setZero();
}

void Solver::ProcessSetZero() {
	P_Jacobian_.setZero();
	Q_Jacobian_.setZero();
	P_.setZero();
	//P_s1.setZero();
	Q_.setZero();
	//Q_s1.setZero();
	C_.setZero();
}

void Solver::Solve()
{
	int num_t = t_end_ / dt_;
	for (int i = 0; i < num_t; i++) {
		double tList[2] = { i * dt_,(i + 1) * dt_ };
		time_result_vec_.push_back((i + 1) * dt_);
		E_Integral_.setZero();
		ProcessEIntegral(tList);//填E_Integral，每个时间循环填一次，不参与Newton的循�?

		my_newton_->PerformNewton();
		x_s2_ = x_;
		x_ = x_newton_;
		P_s1_ = P_;
		Q_s2_ = Q_s1_;
		Q_s1_ = Q_;
		C_s2_ = C_s1_;
		C_s1_ = C_;
		x_result_vec_.push_back(x_);
	}
}

void Solver::SaveResultData()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	//CircuitVarsData
	string output_dir_path = path + "/CircuitVarsData";
	string output_path = output_dir_path + "/CircuitVars.txt";
	output_->SaveTxt(output_path, x_result_vec_, size_);

	//Plot
	//遍历cmd中plot内容
	map<string, PlotStr> plot_map = my_circuit_->plot_compare_;
	for (auto plot_index = plot_map.begin(); plot_index != plot_map.end(); plot_index++)
	{
		//PlotData
		//获取当前plot的生成文件名称
		string plot_dir_path = path + "/PlotData";
		string plot_path = plot_dir_path + "/" + plot_index->first;
		PlotStr current_plot = plot_index->second;
		vector<PlotVIStr> plot_vi_vec = current_plot.plot_vi_vec;
		//获取当前plot的生成列数
		int size_plot = plot_vi_vec.size();

		//按照时间步数，也就是结果文件的行数遍历（行）
		for (int row_index = 0; row_index < x_result_vec_.size(); row_index++)
		{
			// x这一行的值
			Eigen::VectorXd x_result = std::get<Eigen::VectorXd>(x_result_vec_[row_index]);
			// plot一行的值初始化
			Eigen::VectorXd plot_result = Eigen::VectorXd::Zero(size_plot);

			//获取当前plot的生成要求（列）
			for (int plot_vi_index = 0; plot_vi_index < plot_vi_vec.size(); plot_vi_index++)
			{
				PlotVIStr plot_vi_iter = plot_vi_vec[plot_vi_index];
				//类型 time() v() i()
				int plot_type = plot_vi_iter.plot_type;
				//内容
				vector<string> plot_value_vec = plot_vi_iter.plot_value_vec;

				//time()
				if (plot_type == 0)
				{
					plot_result(plot_vi_index) = time_result_vec_[row_index];
				}
				//v()
				else if (plot_type == 1)
				{
					//对比找到列
					if (plot_value_vec.size() == 1)
					{
						//端口号代表的列
						int x_column_index = my_circuit_->port_compare_[plot_value_vec[0]];

						plot_result(plot_vi_index) = x_result(x_column_index);
					}
					//对比找到列然后相减
					else if (plot_vi_iter.plot_value_vec.size() == 2)
					{
						int x_column_index = my_circuit_->port_compare_[plot_value_vec[0]];
						int x_column_index_next = my_circuit_->port_compare_[plot_value_vec[1]];

						plot_result(plot_vi_index) = x_result(x_column_index) - x_result(x_column_index_next);
					}
				}
				//i()
				else if (plot_type == 2)
				{
					//对比找到器件端口号顺序
					vector<string> port_vec = my_circuit_->device_port_compare_[plot_value_vec[0]];
					//获取额外电流项的值
					vector<int> additional_vec = my_circuit_->device_additional_compare_[plot_value_vec[0]];
					if (additional_vec.size() == 1)
					{
						//判断正方向
						if (plot_value_vec[1] == port_vec[0])
						{
							// 正方向
							plot_result(plot_vi_index) = x_result(additional_vec[0]);
						}
						else if (plot_value_vec[1] == port_vec[1])
						{
							// 反方向 需要乘以-1
							plot_result(plot_vi_index) = -1 * x_result(additional_vec[0]);
						}
					}
				}
			}
			// 一行一行的存
			plot_result_vec_.push_back(plot_result);
		}
		output_->SaveTxt(plot_path, plot_result_vec_, size_plot);
		plot_result_vec_.clear();
	}
}

int Solver::GetSize() {
	return size_;
}

Solver::~Solver() {
}