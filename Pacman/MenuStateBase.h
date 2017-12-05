#pragma once
#include "Button.h"
#include "IGameState.h"

class MenuStateBase:public IGameState
{
protected:
	std::vector<std::shared_ptr<GameObject>>_objects;
public:
	void SetObjects(const std::vector<std::shared_ptr<GameObject>>& gameObjects);
};
