#pragma once
#include <tuple>
#include "IDrawable.h"
#include <vector>
#include <memory>
#include "Wrapper.h"
#include <SDL.h>
#include "IClearable.h"

class Surface;
struct Texture;
struct Color;
struct Rect;

class IRenderer:public IClearable
{
public:
	virtual void SetRenderDrawColor(Color color) = 0;

	virtual Wrapper<SDL_Texture>CreateTextureFrom(Wrapper<SDL_Surface>&surface) = 0;

	virtual void CopyEx(Wrapper<SDL_Texture>& texture, Rect* source, Rect* destination) = 0;

	virtual void DrawRect(Rect rect) = 0;

	virtual void FillRect(Rect rect) = 0;

	virtual void Present() = 0;	

	IRenderer() {}

	virtual ~IRenderer() {}
};

