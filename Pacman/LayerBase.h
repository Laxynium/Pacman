#pragma once
#include <string>
#include "IDrawable.h"

class LayerBase :public IDrawable
{
protected:
	const std::string&_type;
	bool _isCollidable = false;
public:
	LayerBase(const std::string&type);
};
