#include "MenuStateBase.h"

void MenuStateBase::SetObjects(const std::vector<std::shared_ptr<GameObject>>& gameObjects)
{
	_objects = gameObjects;
}
