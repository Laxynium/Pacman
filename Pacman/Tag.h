#pragma once
#include "EnumParser.h"

enum class Tag
{
	Pickable, Player, Wall, Enemy, SuperBall,Invulnerable,None,WallToPlayer, Frightened
};

inline EnumParser<Tag>::EnumParser()
{
	enumMap["pickable"] = Tag::Pickable;
	enumMap["picker"] = Tag::Player;
	enumMap["wall"] = Tag::Wall;
	enumMap["enemy"] = Tag::Enemy;
	enumMap["superball"] = Tag::SuperBall;
	enumMap["invulnerable"] = Tag::Invulnerable;
	enumMap["none"] = Tag::None;
	enumMap["walltoplayer"] = Tag::WallToPlayer;
	enumMap["frightened"] = Tag::Frightened;
}
