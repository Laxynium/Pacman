#pragma once
#include <map>

template <typename T>
class EnumParser
{
	std::map<std::string, T> enumMap;
public:
	EnumParser() {};

	T ParseSomeEnum(const std::string &value)
	{
		std::map <std::string, T>::const_iterator iValue = enumMap.find(value);
		if (iValue == enumMap.end())
			throw std::runtime_error("");
		return iValue->second;
	}
};
