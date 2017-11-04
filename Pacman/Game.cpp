#include "Game.h"
#include "IInputHandler.h"
#include "SDLActionType.h"
#include "Square.h"
#include "Color.h"
#include "FromJsonLevelLoader.h"
#include "SpecialSDLActionType.h"


Game::Game(std::shared_ptr<IRenderer>renderer, std::unique_ptr<IInputHandler> inputHandler,
	std::shared_ptr<ILevelLoader>levelLoader, shared_ptr<ICollisionManager>collisionManager) :
	_input_handler(std::move(inputHandler)), _renderer(renderer),
	_levelLoader(levelLoader), _collisionManager(collisionManager)
{
	auto *square_1 = new Square(*_renderer, *_collisionManager);
	_collisionManager->Register(*square_1);
	drawable.reset(square_1);
	drawable->SetPostion({ 32, 32 });

	auto*square_2 = new Square(*_renderer, *_collisionManager);
	_collisionManager->Register(*square_2);
	drawable2.reset(square_2);
	drawable2->SetPostion({ 96, 96 });

	_balls.push_back(std::make_unique<Ball>(*_renderer,make_pair<int,int>(64,32)));
	_balls.push_back(std::make_unique<Ball>(*_renderer,make_pair<int,int>(96,32)));
	_balls.push_back(std::make_unique<Ball>(*_renderer,make_pair<int,int>(128,32)));
	_balls.push_back(std::make_unique<Ball>(*_renderer,make_pair<int,int>(160,32)));	
	_balls.push_back(std::make_unique<Ball>(*_renderer, make_pair<int, int>(192, 32)));

	for (auto&ball : _balls)
		_collisionManager->Register(dynamic_cast<Ball&>(*ball));

	BindInput();

	_level=std::move(_levelLoader->LoadLevel("Assets/PacmanTiled.json"));
}

void Game::BindInput()
{
	std::vector<std::pair<ActionType*, std::function<void()>>>actions;
	actions.emplace_back(std::make_pair(new SDLActionType(SDL_QUIT, 0), [&]() {_isRunning = false; }));

	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_W }, [&]()
	{
		drawable->Move({ 0,-2 });
	}));
	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_S }, [&]()
	{
		drawable->Move({ 0,2 });
	}));
	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_A }, [&]()
	{
		drawable->Move({ -2,0 });
	}));
	actions.emplace_back(std::make_pair(new SpecialSDLActionType{ SDL_SCANCODE_D }, [&]()
	{
		drawable->Move({ 2,0 });
	}));

	_input_handler->SetBindings(actions);
}

bool Game::IsRunning() const
{
	return _isRunning;
}

void Game::Update() const
{
	drawable->Update();
	drawable2->Update();
	for (auto&ball : _balls)
		ball->Update();
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
	 drawable2->Draw();

	 for (auto&ball : _balls)
		 ball->Draw();

	_renderer->Present();
}
