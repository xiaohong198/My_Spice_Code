#include "Input.h"
Input::Input()
	:SpiceString_(nullptr) 
{
	SpiceString_ = new SpiceString();
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
			for (auto iter : SpiceString_->getSplitVec(line, line_trans, "PSET"))
			{
				if (iter != " ")
				{
					scf_str.PSET = iter;
				}
			}
		}

		else if (line_trans.find("DEVICE") != string::npos)
		{
			// DEVICE
			for (auto iter : SpiceString_->getSplitVec(line, line_trans, "DEVICE"))
			{
				if (iter != " ")
				{
					scf_str.DEVICE = iter;
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
				std::vector<std::string> txt_result = SpiceString_->getSplitVec(line, "=");
				if (txt_result.size() == 2)
				{
					std::vector<std::string> split_result = SpiceString_->getSplitVec(txt_result[0], "\t");
					scf_str.ParametersMap.insert({ split_result[split_result.size()-1], txt_result[1] });
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
	cmd_str.IsPest = false;

	while (getline(in, line))
	{
		if (line.find("\t") != string::npos)
		{
			string line_trans = SpiceString_->TransformLow(line);
			if (line_trans.find("_pset") != string::npos)
			{
				cmd_str.IsPest = true;
			}
			if (line_trans.find("(") != string::npos)
			{
				std::vector<std::string> txt_result = SpiceString_->getSplitVec(line, " ");
				cmd_str.Class = SpiceString_->getSplitVec(txt_result[0],"\t")[0];
				cmd_str.Example = txt_result[1];

				string content_str = SpiceString_->getContent(line, "(", ")");
				cmd_str.Port = SpiceString_->getSplitVec(content_str, " ");

				if (line_trans.find("{") != string::npos && line_trans.find("}") != string::npos)
				{
					content_str = SpiceString_->getContent(line, "{", "}");
					for (auto iter : SpiceString_->getSplitVec(content_str, " "))
					{
						std::vector<std::string> split_result = SpiceString_->getSplitVec(iter, "=");
						cmd_str.ParametersMap.insert({ split_result[0], split_result[1] });
					}
					InputCMDStrVec.push_back(cmd_str);
					cmd_str = *(new InputCMDStr);
					cmd_str.IsPest = false;
					continue;
				}
				if (line_trans.find("{") != string::npos && line_trans.find("}") == string::npos)
				{
					std::vector<std::string> txt_result = SpiceString_->getSplitVec(line, "=(");
					pwl_key = SpiceString_->getContent(line, "{", "=(");
					pwl_value += txt_result[txt_result.size() - 1];
				}
			}
			else if (line_trans.find(")}") != string::npos)
			{
				//pwl END
				cmd_str.ParametersMap.insert({ pwl_key, pwl_value });
				InputCMDStrVec.push_back(cmd_str);
				cmd_str = *(new InputCMDStr);
				cmd_str.IsPest = false;
				continue;
			}
			else if (line_trans.find("}") != string::npos)
			{
				//END
				continue;
			}
			else
			{
				//pwl value
				pwl_value += line;
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
		ComparisonStrVec.push_back(comparison_str);
	}
}

void Input::ReadTXT()
{
#if 0
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/CircuitVarsData";
	string outputPath = output_dir_Path + "/Input_Circuit_Diode_level1.txt";

	ifstream fin(outputPath);
	string nowline;
	stringstream sstr;
	int last_sp;
	int nodeMax = 0;
	while (getline(fin, nowline)) {
		int i = 0;
		while (1) {
			if (nowline[i] == 32)
				break;
			i++;
		}//[i]为第一个空格

		int j;
		for (j = nowline.size() - 1; j > i; j--) {
			if (nowline[j] == 32) {
				break;
			}
		}//[j]为最后一个空格
		/*-------------------------------同时预填f,统计type-----------------------------------*/
		vecTimeInvariantDeviceInfo[excitationDeviceCount].deviceType = nowline[0];
		last_sp = i;
		switch (nowline[0]) {
		case 'R':
			vecTimeInvariantDevice.push_back(new Resistor());
			vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xCount = 2;
			for (int h = i + 2; h < j + 1; h++) {
				int portCount = 0;
				if (nowline[h] == ' ') {
					sstr << nowline.substr(last_sp + 1, h - last_sp - 1);
					sstr >> vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
					if (vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount] > nodeMax)
						nodeMax = vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
					last_sp = h;
					portCount++;
				}
			}
			vecTimeInvariantDevice[timeInvariantDeviceCount]->setConstValue(nowline[j + 1] - '0');
			timeInvariantDeviceCount++;
			break;
		case 'C':
			vecTimeInvariantDevice.push_back(new Capacitor());
			vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xCount = 2;
			for (int h = i + 2; h < j + 1; h++) {
				int portCount = 0;
				if (nowline[h] == ' ') {
					sstr << nowline.substr(last_sp + 1, h - last_sp - 1);
					sstr >> vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
					if (vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount] > nodeMax)
						nodeMax = vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
					last_sp = h;
					portCount++;
				}
			}
			vecTimeInvariantDevice[timeInvariantDeviceCount]->setConstValue(nowline[j + 1] - '0');
			timeInvariantDeviceCount++;
			break;
		case 'L':
			vecTimeInvariantDevice.push_back(new Inductor());
			timeInvariantDeviceCount++;
			break;
		case 'V':
			vecExcitationDevice.push_back(new Vsource_DC());
			vecExcitationDeviceInfo[excitationDeviceCount].xCount = 3;
			vecExcitationDeviceInfo[excitationDeviceCount].additionalxCount = 1;
			for (int h = i + 2; h < j + 1; h++) {
				int portCount = 0;
				if (nowline[h] == ' ') {
					sstr << nowline.substr(last_sp + 1, h - last_sp - 1);
					sstr >> vecExcitationDeviceInfo[excitationDeviceCount].xIndex[portCount];
					if (vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount] > nodeMax)
						nodeMax = vecTimeInvariantDeviceInfo[timeInvariantDeviceCount].xIndex[portCount];
					last_sp = h;
					portCount++;
				}
			}
			excitationDeviceCount++;

			break;
			//case 'J':
			//    vecExcitationDevice.push_back(new Jsource());
			//    excitationDeviceCount++;
			//    break;
		case 'D':
			vecTimeVariantDevice.push_back(new Diode());
			timeVariantDeviceCount++;
			break;
		}
	}

	int sumAdditionalxCount = 0;
	for (int i = 0; i < timeInvariantDeviceCount; i++) {
		if (vecTimeInvariantDeviceInfo[i].additionalxCount) {
			int vCount = vecTimeInvariantDeviceInfo[i].xCount - vecTimeInvariantDeviceInfo[i].additionalxCount;
			for (int j = 0; j < vecTimeInvariantDeviceInfo[i].additionalxCount; j++) {
				vecTimeInvariantDeviceInfo[i].xIndex[vCount + j] = nodeMax + sumAdditionalxCount + j;
			}
			sumAdditionalxCount += vecTimeInvariantDeviceInfo[i].additionalxCount;
		}
	}
	for (int i = 0; i < timeVariantDeviceCount; i++) {
		if (vecTimeVariantDeviceInfo[i].additionalxCount) {
			int vCount = vecTimeVariantDeviceInfo[i].xCount - vecTimeVariantDeviceInfo[i].additionalxCount;
			for (int j = 0; j < vecTimeVariantDeviceInfo[i].additionalxCount; j++) {
				vecTimeVariantDeviceInfo[i].xIndex[vCount + j] = nodeMax + sumAdditionalxCount + j;
			}
			sumAdditionalxCount += vecTimeVariantDeviceInfo[i].additionalxCount;
		}
	}
	for (int i = 0; i < excitationDeviceCount; i++) {
		if (vecExcitationDeviceInfo[i].additionalxCount) {
			int vCount = vecExcitationDeviceInfo[i].xCount - vecExcitationDeviceInfo[i].additionalxCount;
			for (int j = 0; j < vecExcitationDeviceInfo[i].additionalxCount; j++) {
				vecExcitationDeviceInfo[i].xIndex[vCount + j] = nodeMax + sumAdditionalxCount + j;
			}
			sumAdditionalxCount += vecExcitationDeviceInfo[i].additionalxCount;
		}
	}
	nodeCount = nodeMax + 1;//认为0节点为地节点
	matrixDimension = nodeCount + sumAdditionalxCount;

#endif // 0

}
