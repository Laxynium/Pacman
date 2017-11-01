#pragma once
#include "IGameBoostrapper.h"

class SDLGameBoostrapper:public IGameBoostrapper
{
	const int FPS = 60;
	const int DELAY_TIME = 1000.0f / FPS;
public:
	void Initialize() override;
	void Run() override;
	SDLGameBoostrapper();
	~SDLGameBoostrapper();
};

