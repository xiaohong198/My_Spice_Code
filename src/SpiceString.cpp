#include "SpiceString.h"
SpiceString::SpiceString() {

}

SpiceString::~SpiceString() {

}

std::vector<std::string> SpiceString::getSplitVec(string str, string str_trans, string delimiter)
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

std::vector<std::string> SpiceString::getSplitVec(string str, string delimiter)
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

string SpiceString::getContent(string _str, string begin_symbol, string end_symbol)
{
	int startIndex = _str.find_first_of(begin_symbol);
	int endIndex = _str.find_last_of(end_symbol);
	string token = _str.substr(startIndex + 1, endIndex - startIndex - 1);
	return token;
}

string SpiceString::TransformUp(string _str)
{
	std::transform(_str.begin(), _str.end(), _str.begin(), ::toupper);
	return _str;
}
string SpiceString::TransformLow(string _str)
{
	std::transform(_str.begin(), _str.end(), _str.begin(), ::tolower);
	return _str;
}
