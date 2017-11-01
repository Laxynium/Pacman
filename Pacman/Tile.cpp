#include "Tile.h"

Rect Tile::GetAreaOfCollision() const
{
	return _rect;
}

Tile::Tile(Rect& rect) :
	_rect(rect)
{
}

Tile::~Tile()
{
}