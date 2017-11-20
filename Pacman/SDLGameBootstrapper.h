#pragma once
#include "IGameBootstrapper.h"

class SDLGameBootstrapper:public IGameBootstrapper
{
	const int FPS = 120;
	const int DELAY_TIME = 1000.0f / FPS;
public:
	void Initialize() override;
	void Run() override;
	SDLGameBootstrapper();
	~SDLGameBootstrapper();
};

