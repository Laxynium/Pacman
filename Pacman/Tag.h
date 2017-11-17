#pragma once
#include "EnumParser.h"

enum class Tag
{
	Pickable,Picker,Blocked,Enemy
};

inline EnumParser<Tag>::EnumParser()
{
	enumMap["pickable"] = Tag::Pickable;
	enumMap["picker"] = Tag::Picker;
	enumMap["blocked"] = Tag::Blocked;
	enumMap["enemy"] = Tag::Enemy;
}
