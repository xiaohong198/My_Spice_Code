#include "SpiceString.h"
SpiceString::SpiceString() {
}

SpiceString::~SpiceString() {
}

std::vector<std::string> SpiceString::GetSplitVec(string _str, string _delimiter, string _str_trans, bool _is_remove)
{
	vector<string> tokens;
	size_t pos = 0;
	string token;
	if (_str_trans != "")
	{
		while ((pos = _str_trans.find(_delimiter)) != string::npos)
		{
			token = _str.substr(0, pos);
			if (!_is_remove)
			{
				token = RemoveChars(token, " ");
			}
			if (token != "")
			{
				token = RemoveChars(token, "\t");
				tokens.push_back(token);
			}
			_str.erase(0, pos + _delimiter.length());
			_str_trans.erase(0, pos + _delimiter.length());
		}
	}
	else
	{
		while ((pos = _str.find(_delimiter)) != string::npos)
		{
			token = _str.substr(0, pos);
			if (!_is_remove)
			{
				token = RemoveChars(token, " ");
			}
			if (token != "")
			{
				token = RemoveChars(token, "\t");
				tokens.push_back(token);
			}
			_str.erase(0, pos + _delimiter.length());
		}
	}

	if (!_is_remove)
	{
		_str = RemoveChars(_str, " ");
	}

	if (_str != "")
	{
		_str = RemoveChars(_str, "\t");
		tokens.push_back(_str);
	}
	return tokens;
}

std::string SpiceString::GetContent(string _str, string _begin_symbol, string _end_symbol)
{
	int start_index = _str.find_first_of(_begin_symbol);
	int end_index = _str.find_last_of(_end_symbol);
	string token = _str.substr(start_index + 1, end_index - start_index - 1);
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