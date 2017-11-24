#pragma once
#include "ICollidable.h"
#include <string>

class Tile : public ICollidable
{
	Rect _dscrect;
	Rect _srcrect;
	std::string _textureName;
	Tag _tag;
public:
	Rect GetAreaOfCollision() const override;

	Tag GetTag() const override;

	Tile(Rect& dscrect,Rect&srcrect,const std::string&textureName, Tag tag);

	 Rect& DscRect();

	 Rect& SrcRect();

	const std::string& TextureName() const;

	~Tile();
};

