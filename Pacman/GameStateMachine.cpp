#include "GameStateMachine.h"
#include "IInputHandler.h"
#include "SDLActionType.h"
#include "MenuState.h"
#include <string>
#include "PlayState.h"

void GameStateMachine::OnStateEnded()
{
	_gameStates.back()->OnExit();

	_temporaryState = _gameStates.back();

	_gameStates.pop_back();

	_justRemovedState = true;

	if(_gameStates.empty())
	{
		this->GameHasEnded();
		_currentState = nullptr;
		return;
	}
	_currentState = _gameStates.back();

	_currentState->OnEnter();
}

void GameStateMachine::OnPushedState(const std::string& stateName)
{
	if (_currentState->GetStateName() == stateName)
		return;

	auto playState = _gameStateFactory->CreateState(stateName);

	if (playState == nullptr)return;

	playState->PushedState += [this](const auto&name) {OnPushedState(name); };

	playState->ChangedState += [this](const auto&name) {OnChangedState(name); };

	playState->StateEnded += [this]() {OnStateEnded(); };
	
	_gameStates.back()->OnExit();

	_gameStates.push_back(playState);

	_currentState = _gameStates.back();

	_currentState->OnEnter();

	std::cout << "Push state " << stateName << std::endl;
}

void GameStateMachine::OnChangedState(const std::string& stateName)
{
	std::cout << "Changed state " << stateName << std::endl;
}

GameStateMachine::GameStateMachine(std::shared_ptr<IInputHandler>inputHandler,
	std::shared_ptr<GameStateFactory>gameStateFactory):_inputHandler(inputHandler), _gameStateFactory(gameStateFactory)
{
	_inputHandler->AddBindings({ std::make_pair((new SDLActionType(SDL_QUIT, 0))->SetUniuqueName("QuitGame"), [&]()
	{
		this->GameHasEnded();
	}) });

	_gameStates.push_back(std::make_shared<MenuState>(_inputHandler));

	_gameStates.back()->PushedState += [this](const auto&name) {this->OnPushedState(name); };

	_currentState = _gameStates.back();

	_currentState->OnEnter();
}

void GameStateMachine::HandleInput()
{
	if(_currentState!=nullptr)
		_currentState->HandleInput();
}

void GameStateMachine::Update()
{
	if (_currentState != nullptr)
		_currentState->Update();

	if (_temporaryState != nullptr&&_justRemovedState)
	{
		_temporaryState = nullptr;
		_justRemovedState = false;
	}
}

void GameStateMachine::Draw()
{
	if (_currentState != nullptr)
		_currentState->Draw();
}

