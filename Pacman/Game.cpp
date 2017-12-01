#include "Game.h"
#include "Color.h"
#include "SDLActionType.h"
#include "GameStateMachine.h"


Game::Game(std::shared_ptr<IRenderer> renderer, std::shared_ptr<GameStateMachine> gameStateMachine):
	_renderer(renderer),_gameStateMachine(gameStateMachine)
{
	_gameStateMachine->GameHasEnded += [&]() {_isRunning = false; };
	//_gameState->GameHasEnded
}

bool Game::IsRunning() const
{
	return _isRunning;
}

void Game::Update() const
{
	_gameStateMachine->Update();
}

void Game::HandleInput()
{
	_gameStateMachine->HandleInput();
}

void Game::Render() const
{
	_renderer->SetRenderDrawColor(Color{ 0, 0, 0,0 });

	_renderer->Clear();

	_gameStateMachine->Draw();

	_renderer->Present();
}
