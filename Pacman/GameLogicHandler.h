#pragma once
#include <functional>

class GameLogicHandler
{
	std::function<void()>_onGameEnded;
public:
	void GameEnded();
	void SetOnGameEnded(const std::function<void()>& onGameEnded);

	//void PlayerWon(std::function<void()>&action);
	//void PlayerTookUpBall(std::function<void()>&action);//TODO add params to function;
	//void PlayerCollidedWithEnemy(std::function<void()>&action);//TODO add params to function
};
