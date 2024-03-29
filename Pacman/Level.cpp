#include "Level.h"
#include "ITextureManager.h"
#include "Rect.h"
#include <algorithm>
#include <iostream>

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

void Level::Update()
{
	for (auto&layer : _layers)
	{
		layer->Update();
	}
}

Level::~Level()
{
	//std::cout << "I am destroying myself\n";
}
