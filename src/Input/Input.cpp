#include "Input.h"

Input::Input()
	:SpiceString_(nullptr)
{
	SpiceString_ = new SpiceString();

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
	string output_dir_Path = path + "/Config";
	string outputPath = output_dir_Path + "/scf.txt";

	ifstream in(outputPath);
	string line;
	InputStr scf_str;
	while (getline(in, line))
	{
		string line_trans = SpiceString_->TransformUp(line);
		if (line.find("END PSET") != string::npos)
		{
			SCFParameterStrMap.insert({ scf_str.PsetName, scf_str });
			scf_str.ParametersMap.clear();
			//END
		}
		else if (line_trans.find("PSET") != string::npos)
		{
			//PSET
			for (auto iter : SpiceString_->getSplitVec(line, "PSET", line_trans))
			{
				if (iter != " ")
				{
					scf_str.PsetName = iter;
				}
			}
		}

		else if (line_trans.find("DEVICE") != string::npos)
		{
			// DEVICE
			for (auto iter : SpiceString_->getSplitVec(line, "DEVICE", line_trans))
			{
				if (iter != " ")
				{
					scf_str.ClassName = iter;
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
				std::vector<std::string> split_result = SpiceString_->getSplitVec(line, "=");
				if (split_result.size() == 2)
				{
					string parameter_key = split_result[0];
					split_result.erase(split_result.begin());
					scf_str.ParametersMap.insert({ parameter_key, split_result });
				}
			}
		}
	}
}

void Input::ReadCMD()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/Config";
	string outputPath = output_dir_Path + "/cmd.txt";

	ifstream in(outputPath);
	string line;
	string pwl_key;
	InputStr cmd_str;
	vector<string> pwl_value_vec;

	while (getline(in, line))
	{
		if (line.find("\t") != string::npos)
		{
			string line_trans = SpiceString_->TransformLow(line);

			if (line_trans.find("(") != string::npos && line_trans.find("{") != string::npos)
			{
				string content_str = SpiceString_->getContent(line, "(", ")");
				cmd_str.Port = SpiceString_->getSplitVec(content_str, " ");

				std::vector<std::string> txt_result = SpiceString_->getSplitVec(line, " ");
				cmd_str.PsetName = txt_result[0];
				if (line_trans.find("_pset") != string::npos)
				{
					std::vector<std::string> name_result = SpiceString_->getSplitVec(txt_result[0], "_pset");
					cmd_str.ClassName = name_result[0];
				}
				cmd_str.InstanceName = txt_result[1];
			}
			if (line_trans.find("{") != string::npos && line_trans.find("}") != string::npos)
			{
				string content_str = SpiceString_->getContent(line, "{", "}");
				for (auto iter : SpiceString_->getSplitVec(content_str, " "))
				{
					std::vector<std::string> split_result = SpiceString_->getSplitVec(iter, "=");

					string parameter_key = split_result[0];
					split_result.erase(split_result.begin());
					cmd_str.ParametersMap.insert({ parameter_key, split_result });
				}
				CMDParameterStrMap.insert({ cmd_str.InstanceName, cmd_str });
				cmd_str = *(new InputStr);
				continue;
			}
			//pwl
			else if (line_trans.find("(") != string::npos && line_trans.find("{") != string::npos && line_trans.find("}") == string::npos)
			{
				std::vector<std::string> txt_result = SpiceString_->getSplitVec(line, "=(", "", true);
				pwl_key = SpiceString_->getContent(line, "{", "=");
				for (auto iter : SpiceString_->getSplitVec(txt_result[1], " "))
				{
					pwl_value_vec.push_back(iter);
				}

				continue;
			}
			else if (line_trans.find("(") == string::npos && line_trans.find("{") == string::npos && line_trans.find("}") == string::npos)
			{
				if (line == "")
				{
					continue;
				}
				//pwl value
				line = SpiceString_->RemoveChars(line, "\t");
				for (auto iter : SpiceString_->getSplitVec(line, " "))
				{
					pwl_value_vec.push_back(iter);
				}
				continue;
			}
			else if (line_trans.find(")}") != string::npos)
			{
				//pwl END
				cmd_str.ParametersMap.insert({ pwl_key, pwl_value_vec });
				CMDParameterStrMap.insert({ cmd_str.InstanceName, cmd_str });

				cmd_str = *(new InputStr);
				pwl_value_vec.clear();
				continue;
			}
			if (line_trans.find("set(") != string::npos)
			{
				string content_str = SpiceString_->getContent(line, "(", ")");
				std::vector<std::string> txt_result = SpiceString_->getSplitVec(content_str, " ");
				for (auto iter : txt_result)
				{
					std::vector<std::string> split_result = SpiceString_->getSplitVec(iter, "=");
					PortCompareMap.insert({ split_result[0] ,stoi(split_result[1]) });
				}
			}
			if (line_trans.find("hint(") != string::npos)
			{
				string content_str = SpiceString_->getContent(line, "(", ")");
				std::vector<std::string> txt_result = SpiceString_->getSplitVec(content_str, " ");
				for (auto iter : txt_result)
				{
					std::vector<std::string> split_result = SpiceString_->getSplitVec(iter, "=");
					HintCompareMap.insert({ split_result[0] ,stoi(split_result[1]) });
				}
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
		comparison_str.ClassName = name;

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
			comparison_str.ParametersMap.insert({ parameter_name ,parameter_value_vec });
		}
		XMLParameterStrMap.insert({ comparison_str.ClassName, comparison_str });
	}
}

void Input::SetParameter()
{
	for (auto InputCMD_iter = CMDParameterStrMap.begin(); InputCMD_iter != CMDParameterStrMap.end(); InputCMD_iter++)
	{
		InputStr user_str = (InputCMD_iter->second);
		string class_name = user_str.ClassName;
		string pset_name = user_str.PsetName;

		// 融合scf
		if (class_name == "")
		{
			InputStr scf_str = SCFParameterStrMap[pset_name];
			for (auto parameter_iter = scf_str.ParametersMap.begin(); parameter_iter != scf_str.ParametersMap.end(); parameter_iter++)
			{
				user_str.ParametersMap.insert({ parameter_iter->first,parameter_iter->second });
				user_str.ParametersMap[parameter_iter->first] = parameter_iter->second;
			}
			class_name = scf_str.ClassName;
			user_str.ClassName = scf_str.ClassName;
		}
		// 融合xml
		InputStr xml_str = XMLParameterStrMap[class_name];
		for (auto parameter_iter = user_str.ParametersMap.begin(); parameter_iter != user_str.ParametersMap.end(); parameter_iter++)
		{
			xml_str.ParametersMap.insert({ parameter_iter->first,parameter_iter->second });
			xml_str.ParametersMap[parameter_iter->first] = parameter_iter->second;
		}
		user_str.ParametersMap = xml_str.ParametersMap;
		UserParameterStrMap.insert({ user_str.InstanceName,user_str });
	}
}

map<string, InputStr> Input::GetParameter()
{
	return UserParameterStrMap;
}

map<string, int> Input::GetPortCompare()
{
	return PortCompareMap;
}

map<string, int> Input::GetHintCompare()
{
	return HintCompareMap;
}