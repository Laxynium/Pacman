#pragma once
#include <functional>

class EventHandler
{
public:
	static EventHandler* Bind(std::function<void()>&functionToCall);
};

