#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "IGameBootstrapper.h"
#include "SDLGameBootstrapper.h"
#include <future>
#include "Event.h"

int main(int argc, char *args[])
{
	std::unique_ptr<IGameBootstrapper> boostrapper = std::make_unique<SDLGameBootstrapper>();
	boostrapper->Initialize();
	boostrapper->Run();
	
	return 0;
}
