#include "Tile.h"
#include <iostream>

Rect Tile::GetAreaOfCollision() const
{
	Rect r = _dscrect;
	//r.x += 4, r.y += 4, r.w /= 2, r.h /= 2;
	return r;
}


Tag Tile::GetTag() const
{
	return _tag;
}

Tile::Tile(Rect& dscrect, Rect&srcrect, const std::string&textureName,Tag tag) :
	_dscrect(dscrect),_srcrect(srcrect),_textureName(textureName)
{
	_tag = tag;
}

Rect& Tile::DscRect() 
{
	return _dscrect;
}

Rect& Tile::SrcRect() 
{
	return _srcrect;
}

const std::string& Tile::TextureName() const
{
	return _textureName;
}

Tile::~Tile()
{
}
