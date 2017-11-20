#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "IGameBootstrapper.h"
#include "SDLGameBootstrapper.h"
#include <future>
#include "Event.h"

class Empty:public ICollidable
{
public:
	Rect GetAreaOfCollision() const override;
	Tag GetTag() const override;
	void OnCollsion(ICollidable& collidedObject) override;
};

Rect Empty::GetAreaOfCollision() const
{
	return {};
}

Tag Empty::GetTag() const
{
	return Tag::Player;
}

void Empty::OnCollsion(ICollidable& collidedObject)
{
}

class A
{
public:
	Event<ICollidable&>action;
	void Raise()
	{
		auto empty = std::make_shared<Empty>();
		action(*empty);
	}
};

int main(int argc, char *args[])
{
	std::unique_ptr<IGameBootstrapper> boostrapper = std::make_unique<SDLGameBootstrapper>();
	boostrapper->Initialize();
	boostrapper->Run();
	
	return 0;
}
