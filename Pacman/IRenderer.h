#pragma once
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
	IRenderer() = default;

	virtual ~IRenderer() = default;

	virtual void SetRenderDrawColor(Color color) = 0;

	virtual Wrapper<SDL_Texture> CreateTextureFrom(Wrapper<SDL_Surface>&surface) = 0;

	virtual void CopyEx(Wrapper<SDL_Texture>& texture, Rect* source, Rect* destination,double angle = 0) = 0;

	virtual void DrawRect(Rect rect) = 0;

	virtual void FillRect(Rect rect) = 0;

	virtual void FillCircle(int x, int y, int r, Color color)=0;

	virtual void Present() = 0;	

};

