#pragma once
#include "ActionType.h"
#include <SDL.h>

struct SDLActionType:public ActionType
{
public:
	~SDLActionType() override{}
	SDL_EventType eventType;
	SDL_Keycode keyCode;

	SDLActionType() = default;
	SDLActionType(SDLActionType&) = default;
	SDLActionType(SDLActionType&&) = default;
	SDLActionType(SDL_EventType event_type, SDL_Keycode key_code)
		: eventType(event_type),
		  keyCode(key_code)
	{
	}

};


