#include "Game.h"
#include "IInputHandler.h"
#include "SDLActionType.h"
#include "Pacman.h"
#include "Color.h"
#include "FromJsonLevelLoader.h"
#include "SpecialSDLActionType.h"
#include "GameLogicHandler.h"
#include <functional>

Game::Game(std::shared_ptr<IRenderer>renderer, std::unique_ptr<IInputHandler> inputHandler,
	std::shared_ptr<ILevelLoader>levelLoader, std::shared_ptr<ICollisionManager>collisionManager,std::shared_ptr<GameLogicHandler>gameLogicHandler) :
	_input_handler(std::move(inputHandler)), _renderer(renderer),
	_levelLoader(levelLoader), _collisionManager(collisionManager), _gameLogicHandler(gameLogicHandler)
{
	auto *square_1 = new Pacman(*_renderer, *_collisionManager);

	_collisionManager->Register(*square_1);

	_gameLogicHandler->GhostHitPlayer += std::bind(&Pacman::OnBeingHit, square_1);

	drawable.reset(square_1);


	drawable->SetPosition({ 432, 736 });


	BindInput();

	_level=std::move(_levelLoader->LoadLevel("Assets/PacmanTiledTest9.json"));
	
	_gameLogicHandler->GameEnded += [&]()
	{
		_isRunning = false;
	};

}

void Game::BindInput()
{
	std::vector<std::pair<ActionType*, std::function<void()>>>actions;
	actions.emplace_back(std::make_pair(new SDLActionType(SDL_QUIT, 0), [&]() {_isRunning = false; }));

	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_W }, [&]()
	{
		drawable->Move({ 0,-1 });
	}));
	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_S }, [&]()
	{
		drawable->Move({ 0,1 });
	}));
	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_A }, [&]()
	{
		drawable->Move({ -1,0 });
	}));
	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_D }, [&]()
	{
		drawable->Move({ 1,0 });
	}));

	_input_handler->SetBindings(actions);
}

bool Game::IsRunning() const
{
	return _isRunning;
}

void Game::Update() const
{
	_collisionManager->DetectAll();

	_gameLogicHandler->Update();

	_level->Update();

	drawable->Update();

	for (auto &ghost : _ghosts)
	{
		ghost->Update();
	}
}

void Game::HandleInput()
{
	_input_handler->HandleActions();
}

void Game::Render() const
{
	_renderer->SetRenderDrawColor(Color{ 0, 0, 0,0 });

	_renderer->Clear();
	
	_level->Draw();

	 drawable->Draw();

	 for (auto &ghost : _ghosts)
	 {
		 ghost->Draw();
	 }

	_renderer->Present();
}
