#pragma once
struct ActionType
{
	virtual ~ActionType(){}
	virtual const std::string&GetUniqueName();
	virtual ActionType* SetUniuqueName(const std::string&name);
protected:
	std::string _uniqueName;
};

inline const std::string& ActionType::GetUniqueName()
{
	return _uniqueName;
}

inline ActionType* ActionType::SetUniuqueName(const std::string& name)
{
	_uniqueName = name;
	return this;
}

