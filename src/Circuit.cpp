#include "Circuit.h"
#include <iostream>
#include <fstream>
#include <direct.h> 
#include <filesystem> 
#include <io.h>
#define byte my_byte
#include <windows.h>


using namespace std;
Circuit::Circuit() {
	Read_InputTXT();
	//Read_InputXML();
    //Read_Inputfile();

/*-------------------------交流源+Diode+RLC测试-------------------------------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 4;

    //vecTimeVariantDevice.push_back(new Diode());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeVariantDeviceInfo[0]->deviceType = 'D';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 2;

    //vecTimeInvariantDevice.push_back(new Inductor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'L';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 2;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[2] = 5;
    //vecTimeInvariantDevice[0]->setConstValue(1.0e-3);

    //vecTimeInvariantDevice.push_back(new Capacitor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[1]->deviceType = 'C';
    //vecTimeInvariantDeviceInfo[1]->deviceIndexPerClass = 1;
    //vecTimeInvariantDeviceInfo[1]->xCount = 2;
    //vecTimeInvariantDeviceInfo[1]->xIndex[0] = 3;
    //vecTimeInvariantDeviceInfo[1]->xIndex[1] = 0;
    //vecTimeInvariantDevice[1]->setConstValue(1.0e-4);

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[2]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[2]->deviceIndexPerClass = 2;
    //vecTimeInvariantDeviceInfo[2]->xCount = 2;
    //vecTimeInvariantDeviceInfo[2]->xIndex[0] = 3;
    //vecTimeInvariantDeviceInfo[2]->xIndex[1] = 0;
    //vecTimeInvariantDevice[2]->setConstValue(10);

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 4;
    //AdditaionalxCount = 2;
    //matrixDimension = nodeCount + AdditaionalxCount;

 
    /*--------------MOA+Jsource 测试-------------*/
    //vecExcitationDevice.push_back(new Jsource());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'J';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 2;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 1;
    //vecExcitationDevice[0]->setConstValue(1.8);
    //
    //vecTimeVariantDevice.push_back(new MOA());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo);
    //vecTimeVariantDeviceInfo[0]->deviceType = 'MOA';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 0;
    //
    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 2;
    //AdditaionalxCount = 0;
    //matrixDimension = nodeCount + AdditaionalxCount;

    /*--------------SurgeArrester+Vsource_AC+R 测试-------------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 3;

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 2;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 2;
    //vecTimeInvariantDevice[0]->setConstValue(0.01);

    //vecTimeVariantDevice.push_back(new SurgeArrester());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo);
    //vecTimeVariantDeviceInfo[0]->deviceType = 'MOA';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 0;

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 3;
    //AdditaionalxCount = 1;
    //matrixDimension = nodeCount + AdditaionalxCount;

#if 1
	/*-------Mos Level1测试-----*/
	DeviceInfoStr  DeviceInfo;

	vecTimeVariantDevice.push_back(new SpiceMosfet());
	DeviceInfo.deviceType = 'V';
	DeviceInfo.deviceIndexPerClass = 0;
	DeviceInfo.xCount = 6;
	DeviceInfo.xIndex = { 1,2,3,4,5,6 };
	vecTimeVariantDeviceInfo.push_back(DeviceInfo);

	vecDevice.push_back(new SpiceMosfet());
	DeviceInfo.deviceType = 'M';
	DeviceInfo.deviceIndexPerClass = 0;
	DeviceInfo.xCount = 6;
	DeviceInfo.xIndex = { 1,2,3,4,5,6 };
	vecDeviceInfo.push_back(DeviceInfo);


	vecExcitationDevice.push_back(new Vsource_DC());
	DeviceInfo.deviceType = 'V';
	DeviceInfo.deviceIndexPerClass = 0;
	DeviceInfo.xCount = 3;
	DeviceInfo.xIndex = { 1,0,9 };
	vecExcitationDeviceInfo.push_back(DeviceInfo);
	vecExcitationDevice[0]->setConstValue(20);

	vecDevice.push_back(new Vsource_DC());
	DeviceInfo.deviceType = 'V';
	DeviceInfo.deviceIndexPerClass = 1;
	DeviceInfo.xCount = 3;
	DeviceInfo.xIndex = { 1,0,9 };
	vecDeviceInfo.push_back(DeviceInfo);
	vecDevice[1]->setConstValue(20);


	vecExcitationDevice.push_back(new PWLVoltageSource());
	DeviceInfo.deviceType = 'P';
	DeviceInfo.deviceIndexPerClass = 1;
	DeviceInfo.xCount = 3;
	DeviceInfo.xIndex = { 8,5,10 };
	vecExcitationDeviceInfo.push_back(DeviceInfo);

	vecDevice.push_back(new PWLVoltageSource());
	DeviceInfo.deviceType = 'P';
	DeviceInfo.deviceIndexPerClass = 2;
	DeviceInfo.xCount = 3;
	DeviceInfo.xIndex = { 8,5,10 };
	vecDeviceInfo.push_back(DeviceInfo);


	vecDevice.push_back(new Resistor());
	DeviceInfo.deviceType = 'R';
	DeviceInfo.deviceIndexPerClass = 3;
	DeviceInfo.xCount = 2;
	DeviceInfo.xIndex = { 3,8 };
	vecDeviceInfo.push_back(DeviceInfo);
	vecDevice[3]->setConstValue(223.8e-2);

	vecDevice.push_back(new Resistor());
	DeviceInfo.deviceType = 'R';
	DeviceInfo.deviceIndexPerClass = 4;
	DeviceInfo.xCount = 2;
	DeviceInfo.xIndex = { 7,0 };
	vecDeviceInfo.push_back(DeviceInfo);
	vecDevice[4]->setConstValue(1.5e-3);

	vecDevice.push_back(new Inductor());
	DeviceInfo.deviceType = 'L';
	DeviceInfo.deviceIndexPerClass = 5;
	DeviceInfo.xCount = 3;
	DeviceInfo.xIndex = { 5,7,11 };
	vecDeviceInfo.push_back(DeviceInfo);
	vecDevice[5]->setConstValue(1.0e-9);

	//timeInvariantDeviceCount = vecTimeInvariantDevice.size();
	DeviceCount = vecDevice.size();
	timeVariantDeviceCount = vecTimeVariantDevice.size();
	excitationDeviceCount = vecExcitationDevice.size();
	nodeCount = 9;
	AdditaionalxCount = 3;
	matrixDimension = nodeCount + AdditaionalxCount;

#endif // 0

    /*----------SpiceDiode测试---------*/
    //vecExcitationDevice.push_back(new Vsource_AC());
    //vecExcitationDeviceInfo.push_back(new structDeviceInfo());
    //vecExcitationDeviceInfo[0]->deviceType = 'V';
    //vecExcitationDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecExcitationDeviceInfo[0]->xCount = 3;
    //vecExcitationDeviceInfo[0]->xIndex[0] = 1;
    //vecExcitationDeviceInfo[0]->xIndex[1] = 0;
    //vecExcitationDeviceInfo[0]->xIndex[2] = 5;

    //vecTimeVariantDevice.push_back(new SpiceDiode());
    //vecTimeVariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeVariantDeviceInfo[0]->deviceType = 'D';
    //vecTimeVariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeVariantDeviceInfo[0]->xCount = 3;
    //vecTimeVariantDeviceInfo[0]->xIndex[0] = 1;
    //vecTimeVariantDeviceInfo[0]->xIndex[1] = 2;
    //vecTimeVariantDeviceInfo[0]->xIndex[2] = 3;

    //vecTimeInvariantDevice.push_back(new Inductor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[0]->deviceType = 'L';
    //vecTimeInvariantDeviceInfo[0]->deviceIndexPerClass = 0;
    //vecTimeInvariantDeviceInfo[0]->xCount = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[0] = 3;
    //vecTimeInvariantDeviceInfo[0]->xIndex[1] = 4;
    //vecTimeInvariantDeviceInfo[0]->xIndex[2] = 6;
    //vecTimeInvariantDevice[0]->setConstValue(1.0e-3);

    //vecTimeInvariantDevice.push_back(new Capacitor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[1]->deviceType = 'C';
    //vecTimeInvariantDeviceInfo[1]->deviceIndexPerClass = 1;
    //vecTimeInvariantDeviceInfo[1]->xCount = 2;
    //vecTimeInvariantDeviceInfo[1]->xIndex[0] = 4;
    //vecTimeInvariantDeviceInfo[1]->xIndex[1] = 0;
    //vecTimeInvariantDevice[1]->setConstValue(1.0e-4);

    //vecTimeInvariantDevice.push_back(new Resistor());
    //vecTimeInvariantDeviceInfo.push_back(new structDeviceInfo());
    //vecTimeInvariantDeviceInfo[2]->deviceType = 'R';
    //vecTimeInvariantDeviceInfo[2]->deviceIndexPerClass = 2;
    //vecTimeInvariantDeviceInfo[2]->xCount = 2;
    //vecTimeInvariantDeviceInfo[2]->xIndex[0] = 4;
    //vecTimeInvariantDeviceInfo[2]->xIndex[1] = 0;
    //vecTimeInvariantDevice[2]->setConstValue(10);

    //timeInvariantDeviceCount = vecTimeInvariantDevice.size();
    //timeVariantDeviceCount = vecTimeVariantDevice.size();
    //excitationDeviceCount = vecExcitationDevice.size();
    //nodeCount = 5;
    //AdditaionalxCount = 2;
    //matrixDimension = nodeCount + AdditaionalxCount;

    /*-----测试coding功能---*/
    //cout << endl;
}

void Circuit::MySplit(string str,string delimiter,vector<string>&tokens)
{
	size_t pos = 0;
	string token;
	while ((pos = str.find(delimiter)) != string::npos)
	{
		token = str.substr(0, pos);
		tokens.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	tokens.push_back(str);
}

void Circuit::Read_InputTXT()
{
	// 获取当前路径
	string path = _getcwd(NULL, 0);
	string output_dir_Path = path + "/Config";
	string outputPath = output_dir_Path + "/InputFile.txt";

	max_electrode = 0;

	//读取txt成一个string
#if 0
	std::ifstream in_txt(outputPath);
	std::ostringstream tmp;
	tmp << in_txt.rdbuf();
	std::string str_txt = tmp.str();
	std::vector<std::string> txt_result;
	MySplit(str_txt, "INSTANCE", txt_result);
#endif // 0

	//特殊类
	SpecialClassNameVec.push_back("Vsource_AC");
	SpecialClassNameVec.push_back("Vsource_DC");
	SpecialClassNameVec.push_back("Inductor");
	SpecialClassNameVec.push_back("PWLVoltageSource");

	InputDataStr input_data;
	InputDataStr input_data_null;
	ifstream in(outputPath);
	bool is_value = false;
	vector<InputDataStr> para;// 存储各字段
	string line;

	while (getline(in, line))
	{
		//开始
		if (line.find("INSTANCE") != string::npos)
		{
			std::vector<std::string> txt_result;
			MySplit(line, "INSTANCE", txt_result);
			for (auto iter : txt_result)
			{
				if (iter!=" ")
				{
					input_data.InstanceName = iter;
				}
			}
		}
		else if (line.find("PSET") != string::npos)
		{
			std::vector<std::string> txt_result;
			MySplit(line, "PSET", txt_result);
			for (auto iter : txt_result)
			{
				if (iter != " ")
				{
					input_data.PSET = iter;
					// 特殊类判断
					vector<string>::iterator it = find(SpecialClassNameVec.begin(), SpecialClassNameVec.end(), iter);
					if (it != SpecialClassNameVec.end())
					{
						input_data.IsSpecial = true;
					}
					else
					{
						input_data.IsSpecial = false;
					}
				}
			}
		}
		else if (line.find("ELECTRODES") != string::npos)
		{
			std::vector<std::string> txt_result;
			MySplit(line, "ELECTRODES", txt_result);
			for (auto iter : txt_result)
			{
				if (iter != " ")
				{
					input_data.EelectrodesVec.push_back(atof(iter.c_str()));
					//特殊类，记录最大值和结构体
					if (input_data.IsSpecial)
					{
						SpecialClassVec.push_back(&input_data);
						if (atof(iter.c_str()) > max_electrode)
						{
							max_electrode = atof(iter.c_str());
						}
					}

				}
			}
		}
		else if (line.find("PARAMETERS") != string::npos)
		{
			is_value = true;
			std::vector<std::string> txt_result;
			MySplit(line, "PARAMETERS", txt_result);
			for (auto iter : txt_result)
			{
				if (iter != " ")
				{
					input_data.EelectrodesVec.push_back(atof(iter.c_str()));
				}
			}
		}
		// 填值
		else if (is_value)
		{
			if (line.find("=") != string::npos)
			{
				std::vector<std::string> txt_result;
				MySplit(line, "=", txt_result);
				for (auto iter : txt_result)
				{
					if (iter != " ")
					{
						string parameter_name;
						string parameter_value;
						if (iter != " ")
						{
							parameter_name;
						}
						else if (iter != " ")
						{
							parameter_value;
						}
						input_data.ParametersMap.insert({ parameter_name, atof(parameter_value.c_str()) });

					}
				}
			}
		}
		//结束
		else if (line.find("END INSTANCE") != string::npos)
		{
			is_value = false;
			para.push_back(input_data);
			input_data = input_data_null;
			continue;
		}
	}
	in.close();
	return;
}

void Circuit::Read_InputXML()
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
	if(!root)
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

#if 0
void Circuit::Read_Inputfile() {
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
}

#endif // 0

Circuit::~Circuit() {
    for (int i = 0; i < DeviceCount; i++) {
        delete vecDevice[i];
    }
    for (int i = 0; i < timeVariantDeviceCount; i++) {
        delete vecTimeVariantDevice[i];
    }
    for (int i = 0; i < excitationDeviceCount; i++) {
        delete vecExcitationDevice[i];
    }
}