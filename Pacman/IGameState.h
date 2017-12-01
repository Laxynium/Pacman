#pragma once
#include "IUpdateable.h"
#include "IDrawable.h"
#include "IClearable.h"
#include "IHandleInput.h"
#include "Event.h"

class IGameState :public IUpdateable, public IDrawable, public IHandleInput
{
protected:
	std::string _stateName;
public:
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	Event<void>StateEnded;
	Event<const std::string&>PushedState;
	Event<const std::string&>ChangedState;
	virtual const std::string& GetStateName();
	virtual IGameState&SetStateName(const std::string&name);
};
