#pragma once
#include "IRenderer.h"
#include <SDL.h>
#include <functional>
#include "Rect.h"
#include "BoostDI.h"
#include "ITextureManager.h"

class SDLRenderer:public IRenderer
{
public:
	template<typename T>
	using Ptr = std::unique_ptr<T, std::function<void(T*)>>;

private:
	const int _gameWidth = 896;
	const int _gameHeight = 1024;
	const double _scale = 0.98;
	Ptr<SDL_Window> _window;
	Ptr<SDL_Renderer> _renderer;
	
	
public:
	SDLRenderer ();
	void SetRenderDrawColor(Color color) override;
	Wrapper<SDL_Texture> CreateTextureFrom(Wrapper<SDL_Surface>& surface) override;
	void Clear() override;
	void DrawRect(Rect rect) override;
	void FillRect(Rect rect) override;
	void FillCircle(int x, int y, int r, Color color) override;
	void CopyEx(Wrapper<SDL_Texture>& textureName, Rect* source, Rect* destination,double angle = 0) override;
	void Present() override;
	
};

