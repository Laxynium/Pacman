#include "GameOverState.h"
#include "GameStateNames.h"
#include "GameLogicHandler.h"
#include <iostream>
#include <string>
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

	int w, h;
	SDL_QueryTexture(&_scoreTexture.Get(), nullptr, nullptr, &w, &h);
	std::cout << w << " " << h << "\n";
	Rect dest{ (896-w)/2,300,w,h };
	_renderer->CopyEx(_scoreTexture, &Rect{ 0,0,w,h }, &dest);
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
	_font = TTF_OpenFont("assets/FFF_Tusj.ttf", 80);
	std::string value=std::to_string(_gameLogicHandler->GetScore());

	SDL_Surface*scoreSurface = TTF_RenderText_Solid(_font, ("Score " + value).c_str(),SDL_Color{255,255,255,0});

	_scoreTexture = _renderer->CreateTextureFrom(Wrapper<SDL_Surface>([](SDL_Surface*s) {SDL_FreeSurface(s); }, scoreSurface));
}

void GameOverState::OnExit()
{
	//TTF_CloseFont(_font);
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
