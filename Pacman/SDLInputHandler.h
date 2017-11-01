#pragma once
#include "IInputHandler.h"
#include <iostream>
#include "ActionType.h"
#include <algorithm>
#include "SpecialSDLActionType.h"
class SDLInputHandler:public IInputHandler
{
	std::vector<std::pair<ActionType*, std::function<void()>>> _onHolded;

	auto SpecialActions();
	auto SDLActions();
public:
	void HandleActions() override;
	SDLInputHandler();
	~SDLInputHandler();
};

