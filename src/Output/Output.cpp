#include "Output.h"

Output::Output()
{
}

Output::~Output() {

}

void Output::SaveTxt(string _path, std::vector<var_t> _data)
{
	// ��ȡ��ǰ·��
	string output_dir_Path = _path + "/../";

	int re = _access(output_dir_Path.c_str(), 0);
	switch (re)
	{
	case -1:
		_mkdir(output_dir_Path.c_str());				//����Ŀ¼
		break;
	default:
		remove(_path.c_str());//ɾ���ļ�
		//_rmdir(output_dir_Path.c_str());//ɾ��Ŀ¼
		_mkdir(output_dir_Path.c_str());				//����Ŀ¼
		break;
	}

	std::stringstream ss;
	//ѭ��
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
