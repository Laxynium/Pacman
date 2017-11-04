#pragma once
#include <functional>
#include <map>
#include <SDL.h>
#include "ActionType.h"
#include <vector>
#include <memory>

class IInputHandler
{
protected:
	std::vector<std::pair<ActionType*, std::function<void()>>> _actions;
public:
	IInputHandler(){}
	virtual ~IInputHandler()
	{
		for(auto&action :_actions)
		{
			if (action.first != nullptr)
				delete action.first;
		}
	}
	virtual void SetBindings(std::vector<std::pair<ActionType*, std::function<void()>>>actions)
	{
		_actions = actions;
	}
	virtual void AddBindings(std::initializer_list<std::pair<ActionType*, std::function<void()>>>actions)
	{
		_actions.insert(_actions.end(),actions.begin(),actions.end());
	}
	virtual void HandleActions() = 0;
};

