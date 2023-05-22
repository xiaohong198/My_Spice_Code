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
	InputSCFStr scf_str;
	while (getline(in, line))
	{
		string line_trans = SpiceString_->TransformUp(line);
		if (line.find("END PSET") != string::npos)
		{
			InputSCFStrVec.push_back(scf_str);
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
					scf_str.DeviceName = iter;
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
	string pwl_value;
	string pwl_key;
	InputCMDStr cmd_str;
	cmd_str.IsPset = false;
	vector<string> pwl_value_vec;

	while (getline(in, line))
	{
		if (line.find("\t") != string::npos)
		{
			string line_trans = SpiceString_->TransformLow(line);
			if (line_trans.find("_pset") != string::npos)
			{
				cmd_str.IsPset = true;
			}
			if (line_trans.find("(") != string::npos)
			{
				std::vector<std::string> txt_result = SpiceString_->getSplitVec(line, " ");
				cmd_str.DeviceType = txt_result[0];
				cmd_str.Instance = txt_result[1];

				string content_str = SpiceString_->getContent(line, "(", ")");
				cmd_str.Port = SpiceString_->getSplitVec(content_str, " ");
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
				InputCMDStrVec.push_back(cmd_str);
				cmd_str = *(new InputCMDStr);
				cmd_str.IsPset = false;
				continue;
			}
			//pwl
			else if (line_trans.find("{") != string::npos && line_trans.find("}") == string::npos)
			{
				std::vector<std::string> txt_result = SpiceString_->getSplitVec(line, "=(","",true);
				pwl_key = SpiceString_->getContent(line, "{", "=");
				for (auto iter : SpiceString_->getSplitVec(txt_result[1], " "))
				{
					pwl_value_vec.push_back(iter);
				}
				
				continue;
			}
			else if (line_trans.find("{") == string::npos && line_trans.find("}") == string::npos)
			{
				//pwl value
				line = SpiceString_->RemoveChars(line, "\t");
				for (auto iter : SpiceString_->getSplitVec(line, " "))
				{
					pwl_value_vec.push_back(iter);
				}
			}
			else if (line_trans.find(")}") != string::npos)
			{
				//pwl END
				cmd_str.ParametersMap.insert({ pwl_key, pwl_value_vec });
				InputCMDStrVec.push_back(cmd_str);
				
				cmd_str = *(new InputCMDStr);
				cmd_str.IsPset = false;
				pwl_value_vec.clear();
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
		printf("Could not load test file %s. Error='%s'. Exiting.\n", outputPath, doc.ErrorDesc());
		return;
	}
	TiXmlElement* root = doc.RootElement();
	if (!root)
	{
		printf("Path is falth");
		return;
	}
	for (TiXmlNode* Class = root->FirstChild("Class");
		Class;
		Class = Class->NextSibling("Class"))
	{
		ComparisonStr comparison_str;
		TiXmlNode*  ClassName = Class->FirstChild("ClassName");
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
			TiXmlNode*  ParameterName = Parameter->FirstChild("ParameterName");
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
		DefaultParameterStrVec.push_back(comparison_str);
	}
}

void Input::SetParameter()
{
	map<string, vector<string>> user_cmd_scf_map;
	UserParameterStrVec = DefaultParameterStrVec;
	for (auto InputCMD_iter : InputCMDStrVec)
	{
		user_cmd_scf_map = InputCMD_iter.ParametersMap;

		string name = InputCMD_iter.DeviceType;

		if (InputCMD_iter.IsPset)
		{
			name = (SpiceString_->getSplitVec(name, "_pset"))[0];
		}
		else
		{
			auto InputSCF_iter = std::find_if(InputSCFStrVec.begin(), InputSCFStrVec.end(), [name](const InputSCFStr& comparison) {
				return comparison.PsetName == name;
			});
			if (InputSCF_iter != InputSCFStrVec.end())
			{
				name = InputSCF_iter->DeviceName;
				for (auto Parameters_iter = InputSCF_iter->ParametersMap.begin(); Parameters_iter != InputSCF_iter->ParametersMap.end(); ++Parameters_iter) {
					{
						user_cmd_scf_map.insert({ Parameters_iter->first,Parameters_iter->second });
					}
				}
			}
		}
		auto UserParameter_iter = std::find_if(UserParameterStrVec.begin(), UserParameterStrVec.end(), [name](const ComparisonStr& comparison) {
			return comparison.ClassName == name;
		});
		if (UserParameter_iter != UserParameterStrVec.end())
		{
			for (auto user_cmd_scf_iter = user_cmd_scf_map.begin(); user_cmd_scf_iter != user_cmd_scf_map.end(); ++user_cmd_scf_iter) {
				{
					UserParameter_iter->ParametersMap.insert({ user_cmd_scf_iter->first,user_cmd_scf_iter->second });
				}
			}
		}
	}
}

