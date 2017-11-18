#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "IGameBoostrapper.h"
#include "SDLGameBoostrapper.h"
#include <future>

int main(int argc, char *args[])
{
	std::unique_ptr<IGameBoostrapper> boostrapper = std::make_unique<SDLGameBoostrapper>();
	
	boostrapper->Initialize();
	boostrapper->Run();
	
	return 0;
}
