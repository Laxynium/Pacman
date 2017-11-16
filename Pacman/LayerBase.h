#pragma once
#include <string>
#include "IDrawable.h"
#include "ObjectBase.h"

class LayerBase :public ObjectBase 
{
protected:
	const std::string&_type;
	bool _isCollidable = false;
public:
	LayerBase(const std::string&type);
};
