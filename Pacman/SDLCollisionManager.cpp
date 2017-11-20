#include "SDLCollisionManager.h"
#include <algorithm>


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

bool SDLCollisionManager::DetectCollision(ICollidable & object, Tag withWhat)
{
	for(auto*otherObject:_objectsToDectection)
	{
		if (otherObject == &object||otherObject->GetTag()!=withWhat)
			continue;

		if (IsCollisionBetween(otherObject, &object))
		{
			return true;
		}			
	}

	return false;
}

void SDLCollisionManager::Register(ICollidable & object)
{
	_objectsToDectection.push_back(&object);
}

void SDLCollisionManager::Subscribe(Tag objectA, Tag objectB,
	std::function<void(ICollidable&, ICollidable&)> onCollison)
{
	_subscribers.push_back({ {objectA,objectB},onCollison});
}

void SDLCollisionManager::DetectAll()
{
	for(int i=0;i<_objectsToDectection.size();++i)
	{
		auto*object = _objectsToDectection[i];

		for(int j=i+1;j<_objectsToDectection.size();++j)
		{
			auto*otherObject = _objectsToDectection[j];

			if (object == otherObject)
				continue;

			if(IsCollisionBetween(object,otherObject))
			{
				std::vector<Element>matches;
				auto sub = std::copy_if(_subscribers.begin(), _subscribers.end(),std::back_inserter(matches),[&](Element&pair)
				{
					return (pair.first.first == object->GetTag() && pair.first.second == otherObject->GetTag())
						|| (pair.first.second == object->GetTag() && pair.first.first == otherObject->GetTag());

				});
				for (auto& sub :matches)
				{
					sub.second(*object, *otherObject);
				}
			}
		}
	}
}

void SDLCollisionManager::Deregister(ICollidable& object)
{
	 auto objectToDeregister=std::find_if(_objectsToDectection.begin(), _objectsToDectection.end(),[&](ICollidable *a)
	{
		 return a == &object;
	});
	 if(objectToDeregister!=_objectsToDectection.end())
		_objectsToDectection.erase(objectToDeregister);
}
