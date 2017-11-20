#pragma once
#include "ICollisionManager.h"
#include "Event.h"

class GameLogicHandler
{
	ICollisionManager& _collisionManager;
	void OnPlayerPickedSuperBall(ICollidable&A,ICollidable&B);
	static ICollidable&GetCollidableWith(Tag tag, ICollidable&A, ICollidable&B);
public:
	GameLogicHandler(GameLogicHandler&) = delete;
	GameLogicHandler(GameLogicHandler&&) = default;
	GameLogicHandler(ICollisionManager&collisionManager): _collisionManager(collisionManager) 
	{
		_collisionManager.Subscribe(Tag::Player, Tag::SuperBall, [this](auto&A, auto&B) {this->OnPlayerPickedSuperBall(A, B); });
	}

	Event<ICollidable&>PlayerPickedSuperBall;

};

