#include "Input.h"
Input::Input()
	:spice_string_(nullptr)
{
	spice_string_ = new SpiceString();

	ReadCompareXML();
	ReadCMD();
	ReadSCF();
	SetParameter();
}

Input::~Input() {
}

void Input::ReadSCF()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_path = path + "/Config";
	string output_path = output_dir_path + "/scf.txt";

	ifstream in(output_path);
	string line;
	InputStr scf_str;
	while (getline(in, line))
	{
		string line_trans = spice_string_->TransformUp(line);
		if (line.find("END PSET") != string::npos)
		{
			scf_compare_.insert({ scf_str.pset_name, scf_str });
			scf_str.parameters_map.clear();
			//END
		}
		else if (line_trans.find("PSET") != string::npos)
		{
			//PSET
			for (auto iter : spice_string_->GetSplitVec(line, "PSET", line_trans))
			{
				if (iter != " ")
				{
					scf_str.pset_name = iter;
				}
			}
		}

		else if (line_trans.find("DEVICE") != string::npos)
		{
			// DEVICE
			for (auto iter : spice_string_->GetSplitVec(line, "DEVICE", line_trans))
			{
				if (iter != " ")
				{
					scf_str.class_name = iter;
				}
			}
		}
		else if (line_trans.find("PARAMETERS") != string::npos)
		{
			// PARAMETERS
		}
		else
		{
			// PARAMETERS_VALUE
			if (line.find("=") != string::npos)
			{
				std::vector<std::string> split_result = spice_string_->GetSplitVec(line, "=");
				if (split_result.size() == 2)
				{
					string parameter_key = split_result[0];
					split_result.erase(split_result.begin());
					scf_str.parameters_map.insert({ parameter_key, split_result });
				}
			}
		}
	}
}

void Input::ReadCMD()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_path = path + "/Config";
	string output_path = output_dir_path + "/cmd.txt";

	ifstream in(output_path);
	string line;
	string pwl_key;
	InputStr cmd_str;
	vector<string> pwl_value_vec;

	while (getline(in, line))
	{
		if (line.find("\t") != string::npos)
		{
			string line_trans = spice_string_->TransformLow(line);

			//Name
			if (line_trans.find("(") != string::npos && line_trans.find("{") != string::npos)
			{
				//Port
				string content_str = spice_string_->GetContent(line, "(", ")");
				cmd_str.port = spice_string_->GetSplitVec(content_str, " ");

				//PsetName
				std::vector<std::string> txt_result = spice_string_->GetSplitVec(line, " ");
				cmd_str.pset_name = txt_result[0];
				// ClassName
				if (line_trans.find("_pset") != string::npos)
				{
					std::vector<std::string> name_result = spice_string_->GetSplitVec(txt_result[0], "_pset");
					cmd_str.class_name = name_result[0];
				}
				// InstanceName
				cmd_str.instance_name = txt_result[1];
			}
			// key-value
			if (line_trans.find("{") != string::npos && line_trans.find("}") != string::npos)
			{
				string content_str = spice_string_->GetContent(line, "{", "}");
				for (auto iter : spice_string_->GetSplitVec(content_str, " "))
				{
					std::vector<std::string> split_result = spice_string_->GetSplitVec(iter, "=");

					string parameter_key = split_result[0];
					split_result.erase(split_result.begin());
					cmd_str.parameters_map.insert({ parameter_key, split_result });
				}
				cmd_compare_.insert({ cmd_str.instance_name, cmd_str });
				cmd_str = *(new InputStr);
				continue;
			}
			//pwl begin
			else if (line_trans.find("(") != string::npos && line_trans.find("{") != string::npos && line_trans.find("}") == string::npos)
			{
				std::vector<std::string> txt_result = spice_string_->GetSplitVec(line, "=(", "", true);
				pwl_key = spice_string_->GetContent(line, "{", "=");
				for (auto iter : spice_string_->GetSplitVec(txt_result[1], " "))
				{
					pwl_value_vec.push_back(iter);
				}

				continue;
			}
			// pwl value
			else if (line_trans.find("(") == string::npos && line_trans.find("{") == string::npos && line_trans.find("}") == string::npos)
			{
				if (line == "")
				{
					continue;
				}
				line = spice_string_->RemoveChars(line, "\t");
				for (auto iter : spice_string_->GetSplitVec(line, " "))
				{
					pwl_value_vec.push_back(iter);
				}
				continue;
			}
			//pwl END
			else if (line_trans.find(")}") != string::npos)
			{
				cmd_str.parameters_map.insert({ pwl_key, pwl_value_vec });
				cmd_compare_.insert({ cmd_str.instance_name, cmd_str });

				cmd_str = *(new InputStr);
				pwl_value_vec.clear();
				continue;
			}
			// set
			if (line_trans.find("set(") != string::npos)
			{
				string content_str = spice_string_->GetContent(line, "(", ")");
				std::vector<std::string> txt_result = spice_string_->GetSplitVec(content_str, " ");
				for (auto iter : txt_result)
				{
					std::vector<std::string> split_result = spice_string_->GetSplitVec(iter, "=");
					port_compare_.insert({ split_result[0] ,stoi(split_result[1]) });
				}
				continue;
			}
			// hint
			if (line_trans.find("hint(") != string::npos)
			{
				string content_str = spice_string_->GetContent(line, "(", ")");
				std::vector<std::string> txt_result = spice_string_->GetSplitVec(content_str, " ");
				for (auto iter : txt_result)
				{
					std::vector<std::string> split_result = spice_string_->GetSplitVec(iter, "=");
					hint_compare_.insert({ split_result[0] ,stoi(split_result[1]) });
				}
				continue;
			}
			//Plot
			if (line_trans.find("plot \"") != string::npos)
			{
				PlotStr plot_str;
				PlotVIStr plot_vi_str;
				string content_str_path = spice_string_->GetContent(line, "\"", "\"");
				plot_str.plot_name = content_str_path;
				string content_str_value = spice_string_->GetContent(line, "(", ")");
				std::vector<std::string> txt_result = spice_string_->GetSplitVec(content_str_value, ") ", "", true);
				for (auto iter : txt_result)
				{
					iter = spice_string_->RemoveChars(iter, ")");
					std::vector<std::string> split_result = spice_string_->GetSplitVec(iter, "(", "", true);
					if (split_result[0] == "time")
					{
						plot_vi_str.plot_type = 0;
					}
					else if (split_result[0] == "v")
					{
						plot_vi_str.plot_type = 1;
					}
					else if (split_result[0] == "i")
					{
						plot_vi_str.plot_type = 2;
					}
					if (split_result.size() == 2)
					{
						plot_vi_str.plot_value_vec = spice_string_->GetSplitVec(split_result[1], " ");
					}
					plot_str.plot_vi_vec.push_back(plot_vi_str);
				}
				plot_compare_.insert({ content_str_path, plot_str });
				continue;
			}
		}
	}
}

void Input::ReadCompareXML()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/Config";
	string outputPath = output_dir_Path + "/Comparison.xml";

	TiXmlDocument doc(outputPath.c_str());
	bool loadOkay = doc.LoadFile();
	if (!loadOkay) {
		return;
	}
	TiXmlElement* root = doc.RootElement();
	if (!root)
	{
		return;
	}
	for (TiXmlNode* Class = root->FirstChild("Class");
		Class;
		Class = Class->NextSibling("Class"))
	{
		InputStr comparison_str;
		TiXmlNode* ClassName = Class->FirstChild("ClassName");
		const char* name = ClassName->ToElement()->GetText();
		if (!name)
		{
			continue;
		}
		comparison_str.class_name = name;

		for (TiXmlNode* Parameter = Class->FirstChild("Parameter");
			Parameter;
			Parameter = Parameter->NextSibling("Parameter"))
		{
			TiXmlNode* ParameterName = Parameter->FirstChild("ParameterName");
			const char* parameter_name = ParameterName->ToElement()->GetText();
			if (!parameter_name)
			{
				continue;
			}
			vector<string> parameter_value_vec;
			for (TiXmlNode* ParameterValue = Parameter->FirstChild("ParameterValue");
				ParameterValue;
				ParameterValue = ParameterValue->NextSibling("ParameterValue"))
			{
				const char* parameter_value = ParameterValue->ToElement()->GetText();
				if (!parameter_value)
				{
					continue;
				}
				parameter_value_vec.push_back(parameter_value);
			}
			comparison_str.parameters_map.insert({ parameter_name ,parameter_value_vec });
		}
		xml_compare_.insert({ comparison_str.class_name, comparison_str });
	}
}

void Input::SetParameter()
{
	for (auto InputCMD_iter = cmd_compare_.begin(); InputCMD_iter != cmd_compare_.end(); InputCMD_iter++)
	{
		InputStr user_str = (InputCMD_iter->second);
		string class_name = user_str.class_name;
		string pset_name = user_str.pset_name;

		// 融合scf
		if (class_name == "")
		{
			InputStr scf_str = scf_compare_[pset_name];
			for (auto parameter_iter = scf_str.parameters_map.begin(); parameter_iter != scf_str.parameters_map.end(); parameter_iter++)
			{
				user_str.parameters_map.insert({ parameter_iter->first,parameter_iter->second });
				user_str.parameters_map[parameter_iter->first] = parameter_iter->second;
			}
			class_name = scf_str.class_name;
			user_str.class_name = scf_str.class_name;
		}
		// 融合xml
		InputStr xml_str = xml_compare_[class_name];
		for (auto parameter_iter = user_str.parameters_map.begin(); parameter_iter != user_str.parameters_map.end(); parameter_iter++)
		{
			xml_str.parameters_map.insert({ parameter_iter->first,parameter_iter->second });
			xml_str.parameters_map[parameter_iter->first] = parameter_iter->second;
		}
		user_str.parameters_map = xml_str.parameters_map;
		user_compare_.insert({ user_str.instance_name,user_str });
	}
}

map<string, InputStr> Input::GetParameter()
{
	return user_compare_;
}

map<string, int> Input::GetPortCompare()
{
	return port_compare_;
}

map<string, int> Input::GetHintCompare()
{
	return hint_compare_;
}
map<string, PlotStr> Input::GetPlotCompare()
{
	return plot_compare_;
}