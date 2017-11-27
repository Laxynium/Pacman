#pragma once
#include "ObjectBase.h"
#include "IRenderer.h"

class GameHud:public ObjectBase
{
	IRenderer& _renderer;
public:
	GameHud(IRenderer&renderer): _renderer(renderer) {  }
	void Draw() override;
	void Update() override;
};
