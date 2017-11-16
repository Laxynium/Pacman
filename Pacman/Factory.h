#pragma once
#include <memory>
#include "Level.h"
#include "Ball.h"
#include "Square.h"
#include "TileLayer.h"

class Factory
{
public:
	Factory(ITextureManager&textureManager,IRenderer&renderer,ICollisionManager&collisionManager);
	~Factory();

	///Client is resposible for live of this object
	Level* CreateLevel(std::vector<std::unique_ptr<LayerBase>>&& layers) const;

	Properties::TileLayer* CreateTileLayer(const std::string& type) const;

	///Client is resposible for live of this object
	Ball* CreateBall(const std::pair<int, int>&pos, int width, int height) const;

	///Client is resposible for live of this object
	Square* CreateSquare() const;

	ITextureManager& _textureManager;
	IRenderer& _renderer;
	ICollisionManager& _collisionManager;
};

