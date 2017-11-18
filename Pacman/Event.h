#pragma once
#include <memory>
#include "EventHandler.h"
#include <vector>
template<typename Arg>
class Event
{
	std::vector<std::function<void(Arg)>>_actions;
public:
	void operator()(Arg arg)
	{
		for (auto&action : _actions)
			if (action!=nullptr)
				action(arg);
	}

	Event& operator+=(std::function<void(Arg)>action)
	{
		_actions.push_back(action);
		return *this;
	}

};
template<>
class Event<void>
{
	std::vector<std::function<void()>>_actions;
public:
	void operator()()
	{
		for (auto&action : _actions)
			if (action!=nullptr)
				action();
	}

	Event& operator+=(std::function<void()>action)
	{
		_actions.push_back(action);
		return *this;
	}
};
