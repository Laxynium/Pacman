#include "Factory.h"
#include "Pacman.h"
#include "TileLayer.h"


Factory::Factory(ITextureManager& textureManager, IRenderer& renderer, ICollisionManager& collisionManager): 
	_textureManager(textureManager), _renderer(renderer), _collisionManager(collisionManager)
{
}

Factory::~Factory()
{
}

Level* Factory::CreateLevel(std::vector<std::unique_ptr<LayerBase>>&& layers) const
{
	return new Level(_renderer, std::move(layers), _textureManager, _collisionManager);
}

Properties::TileLayer* Factory::CreateTileLayer(const std::string& type)const
{
	return new Properties::TileLayer(type, _textureManager, _renderer,_collisionManager);
}
Ball * Factory::CreateBall(const Vector2D& pos, int width, int height) const
{
	return new Ball(_renderer,_collisionManager,pos, width,height);
}

Pacman*Factory::CreatePacman() const
{
	return new Pacman(_renderer, _collisionManager);
}

Ghost* Factory::CreateGhost() const
{
	return new Ghost(_renderer, _collisionManager);
}
