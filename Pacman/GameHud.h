#pragma once
#include "ObjectBase.h"
#include "IRenderer.h"
#include <SDL_ttf.h>

class GameHud:public ObjectBase
{
	IRenderer& _renderer;
	std::string _displayedScore = "0";
	const std::string _scoreCaption = "Score";
	std::string _displayedLives = "3";
	const std::string _livesScaption = "Lives";
	TTF_Font * _font;
	bool _livesHasChanged=false;
	Wrapper<SDL_Texture>_livesTexture;
public:
	GameHud(IRenderer& renderer);
	void Draw() override;
	void Update() override;
	void OnScoreChanged(int newScore);
	void OnLivesChanged(int newLivesCount);
};
