#include "Game.h"
#include "IInputHandler.h"
#include "SDLActionType.h"
#include "Pacman.h"
#include "Color.h"
#include "FromJsonLevelLoader.h"
#include "SpecialSDLActionType.h"
#include "GameLogicHandler.h"
#include <functional>
#include "GameHud.h"

Game::Game(std::shared_ptr<IRenderer>renderer, std::unique_ptr<IInputHandler> inputHandler,
	std::shared_ptr<ILevelLoader>levelLoader, std::shared_ptr<ICollisionManager>collisionManager,std::shared_ptr<GameLogicHandler>gameLogicHandler,std::shared_ptr<GameHud>gameHud) :
	_input_handler(std::move(inputHandler)), _renderer(renderer),
	_levelLoader(levelLoader), _collisionManager(collisionManager), _gameLogicHandler(gameLogicHandler), _gameHud(gameHud)
{
	_gameLogicHandler->PlayerScoreChanged += std::bind(&GameHud::OnScoreChanged, _gameHud.get(), std::placeholders::_1);

	_gameLogicHandler->PlayerLivesChanged += std::bind(&GameHud::OnLivesChanged, _gameHud.get(), std::placeholders::_1);

	auto *square_1 = new Pacman(*_renderer, *_collisionManager);

	_collisionManager->Register(*square_1);

	_gameLogicHandler->GhostHitPlayer += std::bind(&Pacman::OnBeingHit, square_1);

	_pacman.reset(square_1);

	_pacman->SetPosition({ 432, 736 });

	BindInput();

	_level=std::move(_levelLoader->LoadLevel("Assets/PacmanTiledTest8.json"));

	_gameLogicHandler->GameEnded += std::bind(&Game::OnGameEnd, this);

	_gameLogicHandler->LevelEnded += std::bind(&Game::OnLevelEnd, this);

}

void Game::OnLevelEnd()
{
	_gameLogicHandler->Clear();

	_gameLogicHandler->PlayerScoreChanged += std::bind(&GameHud::OnScoreChanged, _gameHud.get(), std::placeholders::_1);

	_gameLogicHandler->PlayerLivesChanged += std::bind(&GameHud::OnLivesChanged, _gameHud.get(), std::placeholders::_1);

	_gameLogicHandler->GhostHitPlayer += std::bind(&Pacman::OnBeingHit, _pacman.get());

	//_level.reset(nullptr);
	this->_level = std::move(this->_levelLoader->LoadLevel("Assets/PacmanTiledTest8.json"));
	_pacman->SetPosition({ 432, 736 });

	_gameLogicHandler->GameEnded += std::bind(&Game::OnGameEnd, this);

	_gameLogicHandler->LevelEnded += std::bind(&Game::OnLevelEnd, this);
}

void Game::OnGameEnd()
{
	_isRunning = false;
}

void Game::BindInput()
{
	std::vector<std::pair<ActionType*, std::function<void()>>>actions;
	actions.emplace_back(std::make_pair(new SDLActionType(SDL_QUIT, 0), [&]() {_isRunning = false; }));

	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_W }, [&]()
	{
		_pacman->Move({ 0,-1 });
	}));
	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_S }, [&]()
	{
		_pacman->Move({ 0,1 });
	}));
	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_A }, [&]()
	{
		_pacman->Move({ -1,0 });
	}));
	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_D }, [&]()
	{
		_pacman->Move({ 1,0 });
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

	_pacman->Update();

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

	 _pacman->Draw();

	 for (auto &ghost : _ghosts)
	 {
		 ghost->Draw();
	 }

	 _gameHud->Draw();

	_renderer->Present();
}
