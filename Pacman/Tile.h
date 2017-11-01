#pragma once
#include "ICollidable.h"
class Tile : public ICollidable
{
	Rect _rect;
public:
	Rect GetAreaOfCollision() const override;
	Tile(Rect& rect);

	~Tile();
};

