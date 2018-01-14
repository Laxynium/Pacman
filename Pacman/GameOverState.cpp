#include "GameOverState.h"
#include "GameStateNames.h"

GameOverState::GameOverState(
                             const std::shared_ptr<IInputHandler>& input_handler):
                                                                                   _inputHandler(input_handler)
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
