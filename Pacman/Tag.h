#pragma once
#include "EnumParser.h"

enum class Tag
{
	Pickable, Player, Wall, Enemy, SuperBall
};

inline EnumParser<Tag>::EnumParser()
{
	enumMap["pickable"] = Tag::Pickable;
	enumMap["picker"] = Tag::Player;
	enumMap["blocked"] = Tag::Wall;
	enumMap["enemy"] = Tag::Enemy;
	enumMap["superball"] = Tag::SuperBall;
}
