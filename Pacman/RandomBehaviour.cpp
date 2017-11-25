#include "RandomBehaviour.h"
#include "Ghost.h"
#include <random>

void RandomBehaviour::Update()
{
	 Vector2D position = _ghost->GetPosition();

	 Vector2D oldPosition = position;

	 Vector2D velocity = _ghost->GetVelocity();

	 position += velocity;
	

	 OnTransition(position);

	if(!_collisionManager.DetectCollision(*_ghost,Tag::Wall))
	{
		return;
	}
	
	position = oldPosition;

	_ghost->SetPosition(position);

	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(1, 2);
	auto generate = bind(dist, engine);

	Vector2D switchedVelocity = { velocity.Y(),velocity.X() };
	std::map<int, Vector2D>_moves
	{
		{1,switchedVelocity },
		{2,switchedVelocity*(-1)},
	};

	int randomNumber = generate();

	velocity = _moves[randomNumber];

	OnTransition(oldPosition +velocity);

	if (!_collisionManager.DetectCollision(*_ghost, Tag::Wall))
	{
		_ghost->SetVelocity(velocity);
		return;
	}

	velocity = _moves[randomNumber == 1 ? 2 : 1];

	OnTransition(oldPosition + velocity);

	_ghost->SetVelocity(velocity);

}
