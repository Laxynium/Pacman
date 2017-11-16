#include "Factory.h"
#include "Square.h"
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
	return new Properties::TileLayer(type, _textureManager, _renderer);
}
Ball * Factory::CreateBall(const std::pair<int, int>& pos, int width, int height) const
{
	return new Ball(_renderer,_collisionManager,pos, width,height);
}

Square*Factory::CreateSquare() const
{
	return new Square(_renderer, _collisionManager);
}
