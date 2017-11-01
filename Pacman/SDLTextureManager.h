#pragma once
#include "ITextureManager.h"
#include <map>
#include <memory>
#include "IRenderer.h"

class SDLTextureManager: public ITextureManager
{
private:
	std::shared_ptr<IRenderer>_renderer;
	std::map<std::string, Wrapper<SDL_Texture>>_mappedTextures;
public:
	void LoadTextureFromFile(const std::string& name, const std::string& textureName) override;
	Wrapper<SDL_Texture>& FindTexture(const std::string& textureName) override;
	SDLTextureManager(std::shared_ptr<IRenderer>renderer);
	~SDLTextureManager();
};

