#include "Tile.h"
#include <iostream>

Rect Tile::GetAreaOfCollision() const
{
	Rect r = _dscrect;
	//r.x += 2, r.y += 2, r.w -= 2, r.h -= 2;
	return r;
}

void Tile::OnCollsion(ICollidable& collidedObject)
{
	std::string text = (collidedObject.GetTag() == Tag::Wall) ? ("blocked") : ("pickabe");
	std::cout << "I was hit by " << text << std::endl;
}

Tag Tile::GetTag() const
{
	return _tag;
}

Tile::Tile(Rect& dscrect, Rect&srcrect, const std::string&textureName) :
	_dscrect(dscrect),_srcrect(srcrect),_textureName(textureName)
{
	_tag = Tag::Wall;
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
