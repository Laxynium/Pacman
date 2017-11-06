#include "Level.h"
#include "ITextureManager.h"
#include "Rect.h"
#include <algorithm>

Level::Level(IRenderer&renderer, std::vector<std::unique_ptr<LayerBase>>&&layers,
	ITextureManager &textureManager, ICollisionManager&collisionManager)
	:_layers(std::move(layers)), _renderer(renderer), _textureManager(textureManager), _collisionManager(collisionManager)
{
}

void Level::Draw()
{
	for(auto&layer:_layers)
	{
		layer->Draw();		
	}
}


Level::~Level()
{
}
