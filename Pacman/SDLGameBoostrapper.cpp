#include "SDLGameBoostrapper.h"
#include <SDL.h>
#include "SDLInputHandler.h"
#include "BoostDI.h"
#include "SDLRenderer.h"
#include "Pacman.h"
#include "IRenderer.h"
#include "SDLRenderer.h"
#include <winsock.h>
#include "SDLTextureManager.h"
#include "ILevelLoader.h"
#include "FromJsonLevelLoader.h"
#include "SDLCollisionManager.h"
#include "ILayerParsersCreator.h"
#include "LayerParsersCreator.h"
#include "Factory.h"
#include "IInnerObjectLayerParsersCreator.h"
#include "InnerObjectLayerParsersCreator.h"
namespace di = boost::di;


void SDLGameBoostrapper::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw new std::exception("Could not initialize subsystems.");

	auto injector = di::make_injector(
		di::bind<ILevelLoader>().to<FromJsonLevelLoader>().in(di::singleton),
		di::bind<ITextureManager>().to<SDLTextureManager>().in(di::singleton),
		di::bind<IRenderer>().to<SDLRenderer>().in(di::singleton),
		di::bind<IInputHandler>().to<SDLInputHandler>().in(di::unique),
		di::bind<ICollisionManager>().to<SDLCollisionManager>().in(di::singleton),
		di::bind<LayerParsersCreator>().to<LayerParsersCreator>().in(di::singleton),
		di::bind<GameLogicHandler>().to<GameLogicHandler>().in(di::singleton),
		di::bind<Factory>().to<Factory>().in(di::singleton),
		di::bind<IInnerObjectLayerParsersCreator>().to<InnerObjectLayerParsersCreator>().in(di::singleton)
		);
		_game = injector.create<std::shared_ptr<Game>>();
}

void SDLGameBoostrapper::Run()
{
	Uint32 frameStart, frameTime;

	while (_game->IsRunning())
	{
		frameStart = SDL_GetTicks();

		_game->HandleInput();

		_game->Update();

		_game->Render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime< DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}
}

SDLGameBoostrapper::SDLGameBoostrapper()
{
}


SDLGameBoostrapper::~SDLGameBoostrapper()
{
	SDL_Quit();
}
