#include "SpiceString.h"
SpiceString::SpiceString() {

}

SpiceString::~SpiceString() {

}

std::vector<std::string> SpiceString::getSplitVec(string str, string delimiter, string str_trans, bool is_remove)
{
	vector<string> tokens;
	size_t pos = 0;
	string token;
	if (str_trans != "")
	{
		while ((pos = str_trans.find(delimiter)) != string::npos)
		{
			token = str.substr(0, pos);
			if (!is_remove)
			{
				token = RemoveChars(token, " ");
			}
			if (token != "")
			{
				token = RemoveChars(token, "\t");
				tokens.push_back(token);
			}
			str.erase(0, pos + delimiter.length());
			str_trans.erase(0, pos + delimiter.length());
		}
	}
	else
	{
		while ((pos = str.find(delimiter)) != string::npos)
		{
			token = str.substr(0, pos);
			if (!is_remove)
			{
				token = RemoveChars(token, " ");
			}
			if (token != "")
			{
				token = RemoveChars(token, "\t");
				tokens.push_back(token);
			}
			str.erase(0, pos + delimiter.length());
		}
	}

	if (!is_remove)
	{
		str = RemoveChars(str, " ");
	}

	if (str != "")
	{
		str = RemoveChars(str, "\t");
		tokens.push_back(str);
	}
	return tokens;
}

//std::vector<std::string> SpiceString::getSplitVec(string str, string delimiter, bool is_remove)
//{
//	vector<string> tokens;
//	size_t pos = 0;
//	string token;
//	while ((pos = str.find(delimiter)) != string::npos)
//	{
//		token = str.substr(0, pos);
//		if (token != "")
//		{
//			tokens.push_back(token);
//		}
//		str.erase(0, pos + delimiter.length());
//	}
//	if (!is_remove)
//	{
//		str = RemoveChars(str, " ");
//	}
//
//	if (str != "")
//	{
//		tokens.push_back(str);
//	}
//
//	return tokens;
//}

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

string SpiceString::RemoveChars(string _str, string _chars)
{
	_str.erase(remove(_str.begin(), _str.end(), *(_chars.c_str())), _str.end());
	return _str;
}
