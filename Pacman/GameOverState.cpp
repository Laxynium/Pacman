#include "GameOverState.h"
#include "GameStateNames.h"
#include "GameLogicHandler.h"
#include <iostream>
#include <string>
#include "Text.h"
#include "GameSettings.h"

GameOverState::GameOverState(const std::shared_ptr<IInputHandler>& input_handler,
		const std::shared_ptr<GameLogicHandler>&gameLogicHandler,const std::shared_ptr<IRenderer>&renderer) :
		_inputHandler(input_handler), _gameLogicHandler(gameLogicHandler), _renderer(renderer)

{
	_stateName = GameStateNames::GameOverState;
}

void GameOverState::Draw()
{
	for (auto&object : _objects)
		object->Draw();
}

void GameOverState::Update()
{
	for (auto&object : _objects)
		object->Update();
}

void GameOverState::HandleInput()
{
	_inputHandler->HandleActions();
}

void GameOverState::OnEnter()
{
	std::string value=std::to_string(_gameLogicHandler->GetScore());
	auto text = std::make_shared<Text>(_renderer, "Score " + value, 80);
	text->SetPosition({ static_cast<double>((GameSettings::GameWidth - text->GetWidth()) / 2),300 });
	_objects.push_back(text);
}

void GameOverState::OnExit()
{
}

void GameOverState::BindActionToButton(Button& button)
{
	std::function<void()>func;

	if (button.GetName() == "playAgainButton")
		func = [this]() {this->ChangedState(GameStateNames::PlayState); };

	if (button.GetName() == "menuButton")
		func = [this]() {this->ChangedState(GameStateNames::MainMenuState); };

	button.Clicked += func;
}
