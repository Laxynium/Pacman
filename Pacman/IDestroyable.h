#pragma once
#include <functional>

class IDestroyable
{
	std::function<void()>_onClear;
public:
	virtual void PerformInClear(std::function<void()>func)
	{
		_onClear = func;
	}
	virtual ~IDestroyable()
	{
		if (_onClear != nullptr)
			_onClear();
	}
};
