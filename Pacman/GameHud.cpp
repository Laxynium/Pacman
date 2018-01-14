#include "GameHud.h"
#include "IRenderer.h"
#include <SDL_ttf.h>
#include "Rect.h"

GameHud::GameHud(IRenderer& renderer) : _renderer(renderer), _font(TTF_OpenFont("assets/FFF_Tusj.ttf", 40))
{
	SDL_Surface *livesSurface = TTF_RenderText_Solid(_font, (_livesScaption + " " + _displayedLives).c_str(), SDL_Color{ 255,255,255,0 });

	_livesTexture = _renderer.CreateTextureFrom(Wrapper<SDL_Surface>([](SDL_Surface*s) {SDL_FreeSurface(s); }, livesSurface));
}

void GameHud::Draw()
{
	SDL_Surface *surface=TTF_RenderText_Solid(_font, (_scoreCaption+" "+_displayedScore).c_str(), SDL_Color{ 255,255,255,0 });


	auto texture=_renderer.CreateTextureFrom(Wrapper<SDL_Surface>([](SDL_Surface*surf) {SDL_FreeSurface(surf); }, surface));
	
	if(_livesHasChanged)
	{
		SDL_Surface *livesSurface = TTF_RenderText_Solid(_font, (_livesScaption + " " + _displayedLives).c_str(), SDL_Color{ 255,255,255,0 });

		_livesTexture = _renderer.CreateTextureFrom(Wrapper<SDL_Surface>([](SDL_Surface*s) {SDL_FreeSurface(s); }, livesSurface));
		_livesHasChanged = false;
	}
	
	int w, h;
	SDL_QueryTexture(&texture.Get(), nullptr, nullptr, &w, &h);
	Rect dest{ 100,970,w,h };
	_renderer.CopyEx(texture, &Rect{ 0,0,w,h }, &dest);
	int w2, h2;
	SDL_QueryTexture(&_livesTexture.Get(), nullptr, nullptr, &w2, &h2);
	Rect dest2{ 650,970,w2,h2 };
	_renderer.CopyEx(_livesTexture, nullptr, &dest2);
}

void GameHud::Update()
{
}

void GameHud::OnScoreChanged(int newScore)
{
	_displayedScore=std::to_string(newScore);
}

void GameHud::OnLivesChanged(int newLivesCount)
{
	_livesHasChanged = true;
	_displayedLives = std::to_string(newLivesCount);
}
