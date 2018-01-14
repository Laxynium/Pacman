#pragma once
#include "ActionArg.h"
#include <vector>

class ActiveKeysActionArg:public ActionArg
{
	std::vector<std::string>_activeKeys;
public:
	
	ActiveKeysActionArg(std::vector<std::string>&keys):_activeKeys(keys) {  }

	const std::vector<std::string>& ActiveKeys() const
	{
		return _activeKeys;
	}
};
