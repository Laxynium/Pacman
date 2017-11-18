#pragma once
#include <functional>
#include "Event.h"

class GameLogicHandler
{
public:
	Event<void>GameEnded;

	Event<void> PlayerPickedUpSuperBall;

	Event<void> PlayerPickedUpBall;

	Event<void> PlayerAteEnemy;

	Event<void> EnemyHitPlayer;
	//void PlayerWon(std::function<void()>&action);
	//void PlayerCollidedWithEnemy(std::function<void()>&action);//TODO add params to function
};
