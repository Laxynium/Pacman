#include "SDLTextureManager.h"
#include <SDL_image.h>


void SDLTextureManager::LoadTextureFromFile(const std::string& name, const std::string& textureName)
{
	auto wrapper = Wrapper<SDL_Surface>([](SDL_Surface*s) {SDL_FreeSurface(s); }, IMG_Load(name.c_str()));
	auto texture=_renderer->CreateTextureFrom(wrapper);

	_mappedTextures[textureName] = std::move(texture);

}

Wrapper<SDL_Texture>& SDLTextureManager::FindTexture(const std::string& textureName)
{
	return _mappedTextures.at(textureName);
}


SDLTextureManager::SDLTextureManager(std::shared_ptr<IRenderer>renderer)
	:_renderer(renderer)
{
}


SDLTextureManager::~SDLTextureManager()
{
}
