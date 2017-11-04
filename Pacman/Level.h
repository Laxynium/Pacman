#pragma once
#include <vector>
#include "Layer.h"
#include "IDrawable.h"
#include "IRenderer.h"
#include "Tileset.h"
#include "ITextureManager.h"
#include "Tile.h"
#include "ICollisionManager.h"

class Level:IDrawable
{
private:
	std::vector<Test::Layer>_layers;

	std::vector<Test::Tileset>_tileset;

	IRenderer &_renderer;

	ITextureManager &_textureManager;
	ICollisionManager& _collisionManager;


public:
	Level(IRenderer&renderer,std::vector<Test::Layer>&layers,std::vector<Test::Tileset>tilesets, 
		ITextureManager &textureManager,ICollisionManager&collisionManager);

	void Draw() override;

	~Level();
};

