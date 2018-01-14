#include "GameStateMachine.h"
#include "IInputHandler.h"
#include "SDLActionType.h"
#include "MainMenuState.h"
#include <string>
#include "PlayState.h"
#include "GameStateNames.h"

GameStateMachine::GameStateMachine(std::shared_ptr<IInputHandler>inputHandler,
	std::shared_ptr<GameStateFactory>gameStateFactory, std::shared_ptr<IStatesLoader>statesLoader) :_inputHandler(inputHandler), _gameStateFactory(gameStateFactory), _statesLoader(statesLoader)
{
	_inputHandler->AddBindings({ std::make_pair((new SDLActionType(SDL_QUIT, 0))->SetUniuqueName("QuitGame"), [&]()
	{
		this->GameHasEnded();
	}) });

	auto state = _gameStateFactory->CreateState(GameStateNames::MainMenuState);
	_statesLoader->Load(_statesFileName, state);
	_gameStates.push_back(state);

	SetupStateBindings(_gameStates.back());

	_currentState = _gameStates.back();

	_currentState->OnEnter();
}

void GameStateMachine::SetupStateBindings(std::shared_ptr<IGameState>&state)
{
	state->PushedState += [this](const auto&name) {this->OnPushedState(name); };

	state->ChangedState += [this](const auto&name) {this->OnChangedState(name); };

	state->StateEnded += [this]() {this->OnStateEnded(); };
}

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

	_statesLoader->Load(_statesFileName, state);

	if (state == nullptr)return;

	SetupStateBindings(state);
	
	_gameStates.back()->OnExit();

	_gameStates.push_back(state);

	_currentState = _gameStates.back();

	_currentState->OnEnter();
}

void GameStateMachine::OnChangedState(const std::string& stateName)
{
	_gameStates.back()->OnExit();

	_temporaryState = _gameStates.back();

	_gameStates.pop_back();

	_justRemovedState = true;

	auto state = _gameStateFactory->CreateState(stateName);

	_statesLoader->Load(_statesFileName,state);

	if (state == nullptr)return;

	SetupStateBindings(state);

	for(auto&gameState:_gameStates)
	{
		gameState->OnExit();
	}
	_gameStates.clear();

	_gameStates.push_back(state);

	_currentState = _gameStates.back();

	_currentState->OnEnter();

	//std::cout << "Changed state " << stateName << std::endl;
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

