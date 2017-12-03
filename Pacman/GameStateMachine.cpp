#include "GameStateMachine.h"
#include "IInputHandler.h"
#include "SDLActionType.h"
#include <string>

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

	auto state = _gameStateFactory->CreateState(stateName);

	if (state == nullptr)return;

	state->PushedState += [this](const auto&name) {OnPushedState(name); };

	state->ChangedState += [this](const auto&name) {OnChangedState(name); };

	state->StateEnded += [this]() {OnStateEnded(); };
	
	_gameStates.back()->OnExit();

	_gameStates.push_back(state);

	_currentState = _gameStates.back();

	_currentState->OnEnter();

	std::cout << "Push state " << stateName << std::endl;
}

void GameStateMachine::OnChangedState(const std::string& stateName)
{
	if (_gameStates.empty())
		return;
	_gameStates.back()->OnExit();

	_temporaryState = _gameStates.back();

	_gameStates.pop_back();

	_justRemovedState = true;

	for(auto&state : _gameStates)
	{
		state->OnExit();
	}

	_gameStates.clear();

	auto playState = _gameStateFactory->CreateState(stateName);

	if (playState == nullptr)return;

	playState->PushedState += [this](const auto&name) {OnPushedState(name); };

	playState->ChangedState += [this](const auto&name) {OnChangedState(name); };

	playState->StateEnded += [this]() {OnStateEnded(); };

	_gameStates.push_back(playState);

	_currentState = _gameStates.back();

	_currentState->OnEnter();

	std::cout << "Change state: " << stateName << std::endl;

}

GameStateMachine::GameStateMachine(std::shared_ptr<IInputHandler>inputHandler,
	std::shared_ptr<GameStateFactory>gameStateFactory):_inputHandler(inputHandler), _gameStateFactory(gameStateFactory)
{
	_inputHandler->AddBindings({ std::make_pair((new SDLActionType(SDL_QUIT, 0))->SetUniuqueName("QuitGame"), [&]()
	{
		this->GameHasEnded();
	}) });

	_gameStates.push_back(_gameStateFactory->CreateState("MenuState"));

	_gameStates.back()->PushedState += [this](const auto&name) {this->OnPushedState(name); };

	_gameStates.back()->StateEnded += [this]() {this->OnStateEnded(); };

	_gameStates.back()->ChangedState += [this](const auto&name) {this->OnChangedState(name); };

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

