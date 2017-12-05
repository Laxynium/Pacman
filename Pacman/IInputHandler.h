#pragma once
#include <functional>
#include <map>
#include <SDL.h>
#include "ActionType.h"
#include <vector>
#include <memory>
#include <algorithm>
#include "ActionArg.h"

class IInputHandler
{
protected:
	template<typename ...T>
	using StoredType = std::pair<ActionType*, std::function<void(T...)>>;

	std::vector<StoredType<>> _actions;
	std::vector<StoredType<std::shared_ptr<ActionArg>>>_actionsWithParams;

	auto FindActions(const std::vector<StoredType<>>&vec, std::function<bool(StoredType<>)>func)
	{
		std::vector<StoredType<>>result;

		std::copy_if(vec.begin(), vec.end(), std::back_inserter(result), func);

		return result;
	}
	template<typename T>
	auto FindActions(const std::vector<StoredType<T>>&vec, std::function<bool(StoredType<T>)>func)
	{
		std::vector<StoredType<T>>result;

		std::copy_if(vec.begin(), vec.end(), std::back_inserter(result), func);

		return result;
	}

public:
	IInputHandler(){}
	virtual ~IInputHandler()
	{
		for(auto&action :_actions)
		{
			if (action.first != nullptr)
				delete action.first;
		}

		for (auto&action : _actionsWithParams)
		{
			if (action.first != nullptr)
				delete action.first;
		}

	}
	virtual void SetBindings(std::vector<std::pair<ActionType*, std::function<void()>>>actions)
	{
		_actions = actions;
	}
	virtual void AddBindings(std::vector<std::pair<ActionType*, std::function<void()>>>actions)
	{
		_actions.insert(_actions.end(),actions.begin(),actions.end());
	}

	virtual void AddBindings(std::vector<std::pair<ActionType*, std::function<void(std::shared_ptr<ActionArg>)>>>actions)
	{
		_actionsWithParams.insert(_actionsWithParams.end(), actions.begin(), actions.end());
	}

	virtual void RemoveBinding(const std::string&name)
	{
		const auto where=std::find_if(_actions.begin(),_actions.end(),[&](const auto&action)
		{
			if (action.first->GetUniqueName()== name)
				return true;
			return false;
		});

		if(where!=_actions.end())
		{
			_actions.erase(where);
		}

		const auto where2 = std::find_if(_actionsWithParams.begin(), _actionsWithParams.end(), [&](const auto&action)
		{
			if (action.first->GetUniqueName() == name)
				return true;
			return false;
		});

		if (where2 != _actionsWithParams.end())
		{
			_actionsWithParams.erase(where2);
		}

	}
	virtual void HandleActions() = 0;
};

