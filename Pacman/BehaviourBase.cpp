#include "BehaviourBase.h"
#include "Ghost.h"
#include "GameSettings.h"

void BehaviourBase::OnTransition(Vector2D position)
{
	const int mazeWidth = GameSettings::GameWidth;
	if (position.X()<0)
	{
		position.SetX(mazeWidth + position.X());
	}
	if (position.X() > mazeWidth)
		position.SetX(position.X() - mazeWidth);

	_ghost->SetPosition(position);
}

BehaviourBase::BehaviourBase(ICollisionManager& collisionManager): _collisionManager(collisionManager)
{
	;
}

void BehaviourBase::SetControlledGhost(Ghost* ghost)
{
	_ghost = ghost;
}
