#pragma once
#include "EnumParser.h"

enum class Tag
{
	Pickable,Picker,Blocked
};

inline EnumParser<Tag>::EnumParser()
{
	enumMap["pickable"] = Tag::Pickable;
	enumMap["picker"] = Tag::Picker;
	enumMap["plocked"] = Tag::Blocked;
}
