#include "Game.h"
#include "IInputHandler.h"
#include "SDLActionType.h"
#include "Pacman.h"
#include "Color.h"
#include "FromJsonLevelLoader.h"
#include "SpecialSDLActionType.h"


Game::Game(std::shared_ptr<IRenderer>renderer, std::unique_ptr<IInputHandler> inputHandler,
	std::shared_ptr<ILevelLoader>levelLoader, std::shared_ptr<ICollisionManager>collisionManager,GameLogicHandler&gameLogicHandler) :
	_input_handler(std::move(inputHandler)), _renderer(renderer),
	_levelLoader(levelLoader), _collisionManager(collisionManager), _gameLogicHandler(gameLogicHandler)
{
	auto *square_1 = new Pacman(*_renderer, *_collisionManager);
	_collisionManager->Register(*square_1);
	drawable.reset(square_1);
	drawable->SetPostion({ 32, 32 });

	auto _redGhost = std::make_unique<Ghost>(*_renderer, *_collisionManager);
	_redGhost->SetColor({ 255,0,0,0 });
	_redGhost->SetPostion({32,192});

	auto _blueGhost = std::make_unique<Ghost>(*_renderer, *_collisionManager);
	_blueGhost->SetColor({ 0,0,255,0});
	_blueGhost->SetPostion({ 192,224 });

	auto _greenGhost = std::make_unique<Ghost>(*_renderer, *_collisionManager);
	_greenGhost->SetColor({ 0,255,0,0});
	_greenGhost->SetPostion({ 192,352 });

	auto _pinkGhost = std::make_unique<Ghost>(*_renderer, *_collisionManager);
	_pinkGhost->SetColor({ 255,192,203,0 });
	_pinkGhost->SetPostion({ 192,384 });

	_collisionManager->Register(*_redGhost);
	_collisionManager->Register(*_blueGhost);
	_collisionManager->Register(*_greenGhost);
	_collisionManager->Register(*_pinkGhost);

	_ghosts.emplace_back(std::move(_redGhost));
	_ghosts.emplace_back(std::move(_blueGhost));
	_ghosts.emplace_back(std::move(_greenGhost));
	_ghosts.emplace_back(std::move(_pinkGhost));
	/*_ghosts.insert(_ghosts.end(),{std::move(_redGhost),std::move(_blueGhost),
		std::move(_greenGhost) ,std::move(_pinkGhost) });*/

	BindInput();

	_level=std::move(_levelLoader->LoadLevel("Assets/PacmanTiled.json"));
	_gameLogicHandler.SetOnGameEnded([&]() {_isRunning = false; });
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
