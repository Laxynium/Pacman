#pragma once
#include "ActionType.h"
#include <SDL.h>

struct SDLActiveButtonsActionType :public ActionType
{
public:
	~SDLActiveButtonsActionType() override {}

	SDLActiveButtonsActionType() = default;
	SDLActiveButtonsActionType(SDLActiveButtonsActionType&) = default;
	SDLActiveButtonsActionType(SDLActiveButtonsActionType&&) = default;
};


