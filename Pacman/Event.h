#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "IClearable.h"

template<typename Arg>
class Event:public IClearable
{
	std::vector<std::function<void(Arg)>>_actions;
public:
	Event() = default;
	Event(const Event&event)
	{
		for(auto action:event._actions)
		{
			_actions.push_back(action);
		}
	}
	Event&operator=(const Event&event)
	{
		for (auto action : event._actions)
		{
			_actions.push_back(action);
		}
		return this;
	}
	void operator()(Arg arg)
	{
		for (auto&action : _actions)
			if (action!=nullptr)
				action(arg);
	}

	Event& operator+=(std::function<void(Arg)>action)
	{
		_actions.emplace_back(action);
		return *this;
	}
	void Clear()override
	{
		_actions.clear();
	}
};
template<>
class Event<void>:public IClearable
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
		_actions.emplace_back(action);
		return *this;
	}
	void Clear() override
	{
		_actions.clear();
	}
};
