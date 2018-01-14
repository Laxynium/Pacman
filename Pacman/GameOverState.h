#pragma once
#include "MenuStateBase.h"
#include <SDL_ttf.h>
#include "BoostDI.h"
#include "GameLogicHandler.h"

class GameOverState:public MenuStateBase
{
	Wrapper<SDL_Texture> _scoreTexture;
	TTF_Font * _font;
	std::shared_ptr<IInputHandler> _inputHandler;
	std::shared_ptr<GameLogicHandler>_gameLogicHandler;
	std::shared_ptr<IRenderer> _renderer;
public:
	GameOverState(const std::shared_ptr<IInputHandler>& input_handler, const std::shared_ptr<GameLogicHandler>&gameLogicHandler, 
			const std::shared_ptr<IRenderer>&renderer);

	void Draw() override;

	void Update() override;

	void HandleInput() override;

	void OnEnter() override;

	void OnExit() override;

protected:
	void BindActionToButton(Button& button) override;
};
