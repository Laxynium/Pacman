#pragma once
#include <string>
#include "Wrapper.h"
#include <SDL.h>

struct ITextureManager
{
	virtual void LoadTextureFromFile(const std::string&name,const std::string&textureName) = 0;
	virtual Wrapper<SDL_Texture>& FindTexture(const std::string&textureName) = 0;
	virtual ~ITextureManager(){}
};
