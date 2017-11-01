#include "SDLInitializer.h"

void SDLInitializer::Initilize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

void SDLInitializer::Destroy()
{
	SDL_Quit();
}
