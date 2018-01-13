#pragma once
#include "GameObject.h"
#include "ITextureManager.h"
#include "IRenderer.h"
#include <ctime>

class Caption:public GameObject
{
	std::shared_ptr<IRenderer> _renderer;

	std::shared_ptr<ITextureManager> _textureManager;
	clock_t _animClock = 0;
	int _animDelay = 120;
public:
	Caption(std::shared_ptr<IRenderer> renderer, std::shared_ptr<ITextureManager>textureManager): _renderer(renderer), _textureManager(textureManager) {  }
	void Draw() override;
	void Update() override;

};
