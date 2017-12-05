#include "MenuStateBase.h"

void MenuStateBase::SetObjects(const std::vector<std::shared_ptr<GameObject>>& gameObjects)
{
	_objects = gameObjects;

	for(auto&object:_objects)
	{
		auto *button = dynamic_cast<Button*>(object.get());

		if (nullptr==button)
			continue;

		BindActionToButton(*button);
	}

}
