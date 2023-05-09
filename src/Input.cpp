#include "Input.h"
Input::Input() {

}

Input::~Input() {

}

std::vector<std::string> Input::getSplitVec(string str, string str_trans, string delimiter)
{
	vector<string> tokens;
	size_t pos = 0;
	string token;
	while ((pos = str_trans.find(delimiter)) != string::npos)
	{
		token = str.substr(0, pos);
		if (token != "")
		{
			tokens.push_back(token);
		}
		str.erase(0, pos + delimiter.length());
		str_trans.erase(0, pos + delimiter.length());
	}
	if (str != "")
	{
		tokens.push_back(str);
	}
	return tokens;
}

std::vector<std::string> Input::getSplitVec(string str, string delimiter)
{
	vector<string> tokens;
	size_t pos = 0;
	string token;
	while ((pos = str.find(delimiter)) != string::npos)
	{
		token = str.substr(0, pos);
		if (token != "")
		{
			tokens.push_back(token);
		}
		str.erase(0, pos + delimiter.length());
	}
	if (str != "")
	{
		tokens.push_back(str);
	}

	return tokens;
}

string Input::getContent(string _str, string begin_symbol, string end_symbol)
{
	int startIndex = _str.find_first_of(begin_symbol);
	int endIndex = _str.find_last_of(end_symbol);
	string token = _str.substr(startIndex + 1, endIndex - startIndex - 1);
	return token;
}

string Input::TransformUp(string _str)
{
	std::transform(_str.begin(), _str.end(), _str.begin(), ::toupper);
	return _str;
}
string Input::TransformLow(string _str)
{
	std::transform(_str.begin(), _str.end(), _str.begin(), ::tolower);
	return _str;
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
		string line_trans = TransformUp(line);
		if (line.find("END PSET") != string::npos)
		{
			InputSCFStrVec.push_back(scf_str);
			scf_str.ParametersMap.clear();
			//END
		}
		else if (line_trans.find("PSET") != string::npos)
		{
			//PSET
			for (auto iter : getSplitVec(line, line_trans, "PSET"))
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
			for (auto iter : getSplitVec(line, line_trans, "DEVICE"))
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
				std::vector<std::string> txt_result = getSplitVec(line, "=");
				if (txt_result.size() == 2)
				{
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
	InputCMDStr cmd_str;
	cmd_str.IsPWL = false;
	cmd_str.IsPest = false;

	while (getline(in, line))
	{
		if (line.find("\t") != string::npos)
		{
			string line_trans = TransformLow(line);
			if (line_trans.find("_pset") != string::npos)
			{
				cmd_str.IsPest = true;
			}
			if (line_trans.find("(") != string::npos)
			{
				std::vector<std::string> txt_result = getSplitVec(line, " ");
				cmd_str.Class = getSplitVec(txt_result[0],"\t")[0];
				cmd_str.Example = txt_result[1];

				string content_str = getContent(line, "(", ")");
				cmd_str.NumVec = getSplitVec(content_str, " ");

				if (line_trans.find("pwl") != string::npos)
				{
					//pwl
					cmd_str.IsPWL = true;
					std::vector<std::string> txt_result = getSplitVec(line, "=(");
					std::vector<std::string> split_result = getSplitVec(txt_result[txt_result.size() - 1], " ");
					vector<string> array = { split_result[split_result.size() - 2] ,split_result[split_result.size() - 1] };
					cmd_str.PWL.push_back(array);
				}
				else
				{
					content_str = getContent(line, "{", "}");
					for (auto iter : getSplitVec(content_str, " "))
					{
						std::vector<std::string> split_result = getSplitVec(iter, "=");
						cmd_str.ParametersMap.insert({ split_result[0], split_result[1] });
					}
					InputCMDStrVec.push_back(cmd_str);
					cmd_str = *(new InputCMDStr);
					cmd_str.IsPWL = false;
					cmd_str.IsPest = false;
				}
			}
			else if (line_trans.find(")}") != string::npos)
			{
				//pwl END
				InputCMDStrVec.push_back(cmd_str);
				cmd_str = *(new InputCMDStr);
				cmd_str.IsPWL = false;
				cmd_str.IsPest = false;
			}
			else if (line_trans.find("}") != string::npos)
			{
				//END
				continue;
			}
			else
			{
				//pwl value
				std::vector<std::string> split_result = getSplitVec(line, " ");
				vector<string> array = { split_result[split_result.size() - 2] ,split_result[split_result.size()-1] };
				cmd_str.PWL.push_back(array);
			}
		}
	}
	
}

void Input::ReadXML()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/Config";
	string outputPath = output_dir_Path + "/input.xml";

	//string outputPath = output_dir_Path + "/Input_Circuit_Diode_level.ini";
	//string value;
	//GetPrivateProfileStringA("section", "key", "default_value", &value[0], 256, "test.ini");
	//std::cout << "value:" << value.c_str() << std::endl;

	max_electrode = 0;


	TiXmlDocument doc(outputPath.c_str());
	bool loadOkay = doc.LoadFile();
	if (!loadOkay) {
		printf("Could not load test file %s. Error='%s'. Exiting.\n", outputPath, doc.ErrorDesc());
	}
	TiXmlElement* root = doc.RootElement();
	if (!root)
	{
		printf("Path is falth");
		return;
	}
	//特殊类
	TiXmlNode*  SpecialClass = root->FirstChild("SpecialClass");
	for (TiXmlNode* item = SpecialClass->FirstChild();
		item;
		item = item->NextSibling())
	{
		const char* name = item->ToElement()->GetText();
		if (!name)
		{
			cout << "Input Data Is False!" << endl;
			return;
		}

		SpecialClassNameVec.push_back(name);
	}

	//写入数据
	for (TiXmlNode* item = root->FirstChild("INSTANCE");
		item;
		item = item->NextSibling())
	{
		InputDataStr input_str;

		TiXmlNode*  NAME = item->FirstChild("NAME");
		const char* instance_name = NAME->ToElement()->GetText();
		if (!instance_name)
		{
			cout << "Input Data Is False!" << endl;
			return;
		}
		input_str.InstanceName = instance_name;

		TiXmlNode*  PSET = item->FirstChild("PSET");
		const char* pest_name = PSET->ToElement()->GetText();
		if (!pest_name)
		{
			cout << "Input Data Is False!" << endl;
			return;
		}
		input_str.PSET = pest_name;

		//判断特殊类
		vector<string>::iterator it = find(SpecialClassNameVec.begin(), SpecialClassNameVec.end(), pest_name);
		if (it != SpecialClassNameVec.end())
		{
			input_str.IsSpecial = true;
		}
		else
		{
			input_str.IsSpecial = false;
		}

		TiXmlNode*  ELECTRODES = item->FirstChild("ELECTRODES");
		for (TiXmlNode* electrode = ELECTRODES->FirstChild();
			electrode;
			electrode = electrode->NextSibling())
		{
			const char* electrode_value = electrode->ToElement()->GetText();
			if (!electrode_value)
			{
				cout << "Input Data Is False!" << endl;
				return;
			}
			input_str.EelectrodesVec.push_back(atof(electrode_value));

			//特殊类，记录最大值和结构体
			if (input_str.IsSpecial)
			{
				SpecialClassVec.push_back(&input_str);
				if (atof(electrode_value) > max_electrode)
				{
					max_electrode = atof(electrode_value);
				}
			}
		}

		TiXmlNode*  PARAMETERS = item->FirstChild("PARAMETERS");
		for (TiXmlNode*  PARAMETER = PARAMETERS->FirstChild("PARAMETER");
			PARAMETER;
			PARAMETER = PARAMETER->NextSibling())
		{
			TiXmlNode*  PARAMETER_name = PARAMETER->FirstChild("name");
			const char* parameter_name = PARAMETER_name->ToElement()->GetText();
			if (!parameter_name)
			{
				cout << "Input Data Is False!" << endl;
				return;
			}
			TiXmlNode*  PARAMETER_value = PARAMETER->FirstChild("value");
			const char* parameter_value = PARAMETER_value->ToElement()->GetText();
			if (!parameter_value)
			{
				cout << "Input Data Is False!" << endl;
				return;
			}
			input_str.ParametersMap.insert({ parameter_name, atof(parameter_value) });
		}

		InputDataStrSVec.push_back(input_str);
	}
	//处理特殊类



	//______________________________________________________________________  


	//______________________________________________________________________  
	// Add information to xml file and save it.  
	//TiXmlElement* writeRoot = doc.RootElement();
	//TiXmlNode* newNode = new TiXmlElement("item");

	//const TiXmlNode* name4NewNode = new TiXmlElement("name");
	//newNode->InsertEndChild(*name4NewNode)->InsertEndChild(TiXmlText("pipi"));

	//const TiXmlNode* addr4NewNode = new TiXmlElement("addr");
	//newNode->InsertEndChild(*addr4NewNode)->InsertEndChild(TiXmlText("Shaanxi Xianyang"));

	//const TiXmlNode* tel4NewNode = new TiXmlElement("tel");
	//newNode->InsertEndChild(*tel4NewNode)->InsertEndChild(TiXmlText("02937310627"));

	//const TiXmlNode* email4NewNode = new TiXmlElement("email");
	//newNode->InsertEndChild(*email4NewNode)->InsertEndChild(TiXmlText("pipi@home.com"));

	//writeRoot->InsertEndChild(*newNode);
	//doc.SaveFile();


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

void Input::ReadINI()
{

}

void Input::GetInput(vector<InputDataStr>& input_vec)
{

}
