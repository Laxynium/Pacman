#pragma once
#include "Tileset.h"
#include <vector>
#include "Tag.h"

namespace Properties
{
	class TileLayerProperties
	{
		friend class Layer;

		std::vector<std::vector<int>> _data;

		std::vector<Properties::Tileset> _tilesets;

	public:

		std::vector<Properties::Tileset>& tilesets();

		void SetTilesets(const std::vector<Properties::Tileset>& tilesets);

		void SetData(const std::vector<int>& data);

		std::vector<std::vector<int>> GetData() const;

		std::string Name;

		int Width;

		int Height;

		int X;

		int Y;

		bool IsCollidable;

		Tag Tag;
	};
}


