#pragma once
#include <vector>
#include "IDrawable.h"
#include "IRenderer.h"
#include "Tileset.h"
#include "ITextureManager.h"
#include "Tile.h"
#include "ICollisionManager.h"
#include "LayerBase.h"
#include "ObjectBase.h"

class Level:public ObjectBase
{
private:
	std::vector<std::unique_ptr<LayerBase>>_layers;

	std::vector<Properties::Tileset>_tileset;

	IRenderer &_renderer;

	ITextureManager &_textureManager;
	ICollisionManager& _collisionManager;


public:
	Level(IRenderer&renderer,std::vector<std::unique_ptr<LayerBase>>&&layers,
		ITextureManager &textureManager,ICollisionManager&collisionManager);

	void Draw() override;

	void Update()override;

	~Level();
};

