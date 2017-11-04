#include "Level.h"
#include "ITextureManager.h"
#include "Rect.h"
#include <algorithm>

Level::Level(IRenderer&renderer, std::vector<Test::Layer>& layers, std::vector<Test::Tileset> tilesets,
	ITextureManager &textureManager, ICollisionManager&collisionManager)
	:_layers(layers),_tileset(tilesets),_renderer(renderer), _textureManager(textureManager), _collisionManager(collisionManager)
{
	for(auto&layer:_layers)
	{
		if (!layer.Properties().IsCollidable)
			continue;

		for(auto*tile: layer.GetTiles())
			_collisionManager.Register(*tile);
	}
}

void Level::Draw()
{
	for(auto&layer:_layers)
	{
		layer.Draw();		
	}
}


Level::~Level()
{
}
