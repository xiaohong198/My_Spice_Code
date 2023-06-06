#include "Output.h"

Output::Output()
{
}

Output::~Output() {

}

void Output::SaveTxt(string _path, std::vector<var_t> _data)
{
	// 获取当前路径
	string output_dir_Path = _path + "/../";

	int re = _access(output_dir_Path.c_str(), 0);
	switch (re)
	{
	case -1:
		_mkdir(output_dir_Path.c_str());				//创建目录
		break;
	default:
		remove(_path.c_str());//删除文件
		//_rmdir(output_dir_Path.c_str());//删除目录
		_mkdir(output_dir_Path.c_str());				//创建目录
		break;
	}

	std::stringstream ss;
	//循环
	for (auto& iter : _data)
	{
		if (std::holds_alternative<std::string>(iter))
		{
			ss << std::get<std::string>(iter) << '\n';
		}
		else if (std::holds_alternative<int>(iter))
		{
			ss << std::get<int>(iter) << '\n';
		}
		else if (std::holds_alternative<double>(iter))
		{
			ss << std::setprecision(8) << std::get<double>(iter) << '\n';
		}
		else if (std::holds_alternative<Eigen::VectorXd>(iter))
		{
			for (int i = 0; i < _VectorXd_size; i++)
			{
				ss << std::setprecision(8) << std::get<Eigen::VectorXd>(iter)(i) << ',';
			}
			ss << '\n';
		}
	}
	ofstream OpenF3(_path, ios::trunc | ios::out);
	OpenF3 << ss.str();
	OpenF3.close();
}
