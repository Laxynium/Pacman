#pragma once
#include <SDL.h>

class SpecialSDLActionType:public ActionType
{

public:
	SDL_Keycode KeyCode;
	SpecialSDLActionType(SDL_Keycode keyCode):KeyCode(keyCode){}
};


