#pragma once
#include "ICollisionManager.h"
#include <functional>
#include <vector>

class SDLCollisionManager :
	public ICollisionManager
{
protected:
	std::vector<ICollidable*>_objectsToDectection;

	using Element = std::pair<std::pair<Tag, Tag>, std::function<void(ICollidable&, ICollidable&)>>;

	std::vector<Element> _subscribers;

	static bool IsCollisionBetween(ICollidable* staticobject, ICollidable*  object);

public:
	 bool DetectCollision(ICollidable & object,Tag withWhat) override;

	 void Register(ICollidable & object) override;

	void Subscribe(Tag objectA, Tag objectB, std::function<void(ICollidable&, ICollidable&)>onCollison) override;

	void DetectAll() override;
		
	void Deregister(ICollidable& object) override;

	void DeregisterAll() override;
};

