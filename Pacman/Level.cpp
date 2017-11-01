#include "Level.h"
#include "ITextureManager.h"
#include "Rect.h"
#include <algorithm>

Level::Level(IRenderer&renderer, std::vector<Test::Layer>& layers, std::vector<Test::Tileset> tilesets,ITextureManager &textureManager)
	:_layers(layers),_tileset(tilesets),_renderer(renderer), _textureManager(textureManager)
{
}

vector<Tile*> Level::GetTiles()
{
	vector<Tile*>_tiles;
	for(auto&layer:_layers)
	{
		if(!layer.Properties().IsCollidable)
			continue;

		auto tiles = layer.GetTiles();

		_tiles.insert(_tiles.end(), tiles.begin(), tiles.end());
	}
	return _tiles;
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
