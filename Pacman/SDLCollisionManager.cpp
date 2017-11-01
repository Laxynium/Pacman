#include "SDLCollisionManager.h"


bool SDLCollisionManager::IsCollisionBetween(ICollidable* A, ICollidable* B)
{
	auto area = A->GetAreaOfCollision();

	const int leftA = area.x, topA = area.y;
	const int rightA = leftA+ area.w, botA = topA+area.h;

	area = B->GetAreaOfCollision();

	const int leftB = area.x, topB = area.y;
	const int rightB = leftB+ area.w, botB = topB+ area.h;

	if (botA <= topB)
		return false;

	if (topA >= botB)
		return false;

	if (rightA <= leftB)
		return false;

	if (leftA >= rightB)
		return false;

	//If none of the sides from A are outside B
	return true;
}

bool SDLCollisionManager::DetectCollision(ICollidable & object)
{
	for(auto*staticobject:_objectsToDectection)
	{
		if (staticobject == &object)
			continue;

		if (IsCollisionBetween(staticobject, &object))
			return true;
	}

	return false;
}

void SDLCollisionManager::Register(ICollidable & object)
{
	_objectsToDectection.push_back(&object);
}
