#pragma once
#include <string>
namespace Properties
{
	struct Tileset
	{
		int FirstGridId;
		std::string Source;
		std::string Name;

		int Columns;
		int Rows;
		std::string ImageSource;
		int ImageWidth;
		int ImageHeight;

		int Margin;
		int Spacing;
		int TileCount;
		int TileWidth;
		int TileHeight;
	};
}


