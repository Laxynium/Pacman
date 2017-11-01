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
	Ptr<SDL_Window> _window;
	Ptr<SDL_Renderer> _renderer;
public:
	SDLRenderer ();
	void SetRenderDrawColor(Color color) override;
	Wrapper<SDL_Texture> CreateTextureFrom(Wrapper<SDL_Surface>& surface) override;
	void Clear() override;
	void DrawRect(Rect rect) override;
	void FillRect(Rect rect) override;
	void CopyEx(Wrapper<SDL_Texture>& textureName, Rect* source, Rect* destination) override;
	void Present() override;
	
};

