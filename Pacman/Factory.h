#pragma once
#include <memory>
#include "Level.h"
#include "Ball.h"
#include "Pacman.h"
#include "TileLayer.h"
#include "Ghost.h"

class Factory
{
public:
	Factory(ITextureManager&textureManager,IRenderer&renderer,ICollisionManager&collisionManager);
	~Factory();

	///Client is resposible for live of this object
	Level* CreateLevel(std::vector<std::unique_ptr<LayerBase>>&& layers) const;

	Properties::TileLayer* CreateTileLayer(const std::string& type) const;

	///Client is resposible for live of this object
	Ball* CreateBall(const Vector2D&pos, int width, int height) const;

	///Client is resposible for live of this object
	Pacman* CreatePacman() const;

	Ghost*CreateGhost()const;

	ITextureManager& _textureManager;
	IRenderer& _renderer;
	ICollisionManager& _collisionManager;
};

