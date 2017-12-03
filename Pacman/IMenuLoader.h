#pragma once
#include "GameStateMachine.h"

class IMenuLoader
{
public:	
	virtual std::shared_ptr<IGameState> Create(const std::string&name) = 0;

};
