#include "PlayState.h"
#include "SDLActionType.h"
#include "SpecialSDLActionType.h"
#include <functional>

PlayState::PlayState(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler,
                         std::shared_ptr<ILevelLoader> levelLoader, std::shared_ptr<ICollisionManager> collisionManager,
                         std::shared_ptr<GameLogicHandler> gameLogicHandler, std::shared_ptr<GameHud> gameHud):
	_renderer(renderer), _inputHandler(inputHandler),
	_levelLoader(levelLoader), _collisionManager(collisionManager),
	_gameLogicHandler(gameLogicHandler), _gameHud(gameHud)
{
	_stateName = "PlayState";
	SetupPacman();

	_level = std::move(_levelLoader->LoadLevel(_mapPath));
	
	BindToGameLogicHandler();
}

PlayState::~PlayState()
{
	_collisionManager->DeregisterAll();
	_gameLogicHandler->ClearAll();
}

void PlayState::SetupPacman()
{
	auto *pacman = new Pacman(*_renderer, *_collisionManager);

	_collisionManager->Register(*pacman);

	_gameLogicHandler->GhostHitPlayer += std::bind(&Pacman::OnBeingHit, pacman);

	_pacman.reset(pacman);

	_pacman->SetPosition({ 432, 736 });
}

void PlayState::BindInput()
{
	std::vector<std::pair<ActionType*, std::function<void()>>>actions;

	actions.emplace_back(std::make_pair((new SpecialSDLActionType{ SDL_SCANCODE_W })->SetUniuqueName("WPressed"), [&]()
	{
		_pacman->Move({ 0,-1 });
	}));
	actions.emplace_back(std::make_pair((new SpecialSDLActionType{ SDL_SCANCODE_S })->SetUniuqueName("SPressed"), [&]()
	{
		_pacman->Move({ 0,1 });
	}));
	actions.emplace_back(std::make_pair((new SpecialSDLActionType{ SDL_SCANCODE_A })->SetUniuqueName("APressed"), [&]()
	{
		_pacman->Move({ -1,0 });
	}));
	actions.emplace_back(std::make_pair((new SpecialSDLActionType{ SDL_SCANCODE_D })->SetUniuqueName("DPressed"), [&]()
	{
		_pacman->Move({ 1,0 });
	}));

	actions.emplace_back(std::make_pair((new SpecialSDLActionType{SDL_SCANCODE_ESCAPE})->SetUniuqueName("ESCPressed"),[&]()
	{
		PushedState("PauseState");
	}));

	_inputHandler->AddBindings( actions);
}

void PlayState::BindToGameLogicHandler()
{
	_gameLogicHandler->PlayerScoreChanged += std::bind(&GameHud::OnScoreChanged, _gameHud.get(), std::placeholders::_1);

	_gameLogicHandler->PlayerLivesChanged += std::bind(&GameHud::OnLivesChanged, _gameHud.get(), std::placeholders::_1);

	_gameLogicHandler->GameEnded += std::bind(&PlayState::OnGameEnd, this);

	_gameLogicHandler->LevelEnded += std::bind(&PlayState::OnLevelEnd, this);
}

void PlayState::OnLevelEnd()
{
	//Remove all bindings to gameLogicHandler
	_gameLogicHandler->Clear();
	
	this->_level = std::move(this->_levelLoader->LoadLevel("Assets/PacmanTiledTest8.json"));
	
	//Bind to it not destroyed objects
	_gameLogicHandler->GhostHitPlayer += std::bind(&Pacman::OnBeingHit, _pacman.get());

	BindToGameLogicHandler();

	_pacman->SetPosition({ 432, 736 });
}

void PlayState::OnGameEnd()
{
	//Notifity GameStateMachine that you ended
	ChangedState("MenuState");

	_isRunning = false;
}

void PlayState::OnEnter()
{
	BindInput();
}

void PlayState::HandleInput()
{
	_inputHandler->HandleActions();
}

void PlayState::Update()
{
	_collisionManager->DetectAll();

	_gameLogicHandler->Update();

	_level->Update();

	_gameHud->Update();

	_pacman->Update();
}

void PlayState::Draw()
{
	_level->Draw();

	_pacman->Draw();

	_gameHud->Draw();
}

void PlayState::OnExit()
{
	_inputHandler->RemoveBinding("WPressed");
	_inputHandler->RemoveBinding("SPressed");
	_inputHandler->RemoveBinding("DPressed");
	_inputHandler->RemoveBinding("APressed");
	_inputHandler->RemoveBinding("ESCPressed");
}

