#include "GameHud.h"
#include "IRenderer.h"
#include <SDL_ttf.h>
#include "Rect.h"

GameHud::GameHud(const std::shared_ptr<IRenderer>& renderer) : _renderer(renderer), _font(TTF_OpenFont("assets/FFF_Tusj.ttf", 40))
{
	_lives = std::make_shared<Text>(_renderer, _livesScaption + " " + _displayedLives, 40);
	_lives->SetPosition({ 650,970 });

	_score = std::make_shared<Text>(_renderer, _scoreCaption + " " + _displayedScore, 40);
	_score->SetPosition({ 100,970 });

}

void GameHud::Draw()
{
	_score->Draw();
	_lives->Draw();
}

void GameHud::Update()
{
}

void GameHud::OnScoreChanged(int newScore)
{
	_displayedScore=std::to_string(newScore);
	_score->SetText(_scoreCaption + " " + _displayedScore);
}

void GameHud::OnLivesChanged(int newLivesCount)
{
	_livesHasChanged = true;
	_displayedLives = std::to_string(newLivesCount);
	_lives->SetText(_livesScaption + " " + _displayedLives);
}
