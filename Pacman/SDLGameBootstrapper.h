#pragma once
#include "IGameBootstrapper.h"

class SDLGameBootstrapper:public IGameBootstrapper
{
	const int FPS = 90;
	const int DELAY_TIME = 1000.0f / FPS;
private://methods
	void InitializeComponents();
public:
	void Initialize() override;


	void Run() override;

	SDLGameBootstrapper();

	~SDLGameBootstrapper();
};

