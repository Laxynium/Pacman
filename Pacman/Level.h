#pragma once
#include <vector>
#include "Layer.h"
#include "IDrawable.h"
#include "IRenderer.h"
#include "Tileset.h"
#include "ITextureManager.h"
#include "Tile.h"

class Level:IDrawable
{
private:
	std::vector<Test::Layer>_layers;

	std::vector<Test::Tileset>_tileset;

	IRenderer &_renderer;

	ITextureManager &_textureManager;

public:
	Level(IRenderer&renderer,std::vector<Test::Layer>&layers,std::vector<Test::Tileset>tilesets, ITextureManager &textureManager);

	vector<Tile*>GetTiles();

	void Draw() override;

	~Level();
};

