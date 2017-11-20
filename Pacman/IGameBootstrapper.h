#pragma once
#include "Game.h"

class IGameBootstrapper
{
protected:
	std::shared_ptr<Game> _game;
public:
	virtual void Initialize() = 0;
	virtual void Run() = 0;
	virtual ~IGameBootstrapper(){}
};