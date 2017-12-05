#pragma once
#include "IInputHandler.h"

class SDLInputHandler:public IInputHandler
{
	auto SpecialActions();
	auto SDLActions();
	
public:
	void HandleActions() override;
	SDLInputHandler();
	~SDLInputHandler();
};

