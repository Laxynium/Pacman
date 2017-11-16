#include "TileLayerProperties.h"

std::vector<Properties::Tileset>& Properties::TileLayerProperties::tilesets()
{
	return _tilesets;
}

void Properties::TileLayerProperties::SetTilesets(const std::vector<Properties::Tileset>& tilesets)
{
	_tilesets = tilesets;
}

void Properties::TileLayerProperties::SetData(const std::vector<int>& data)
{
	int r = -1;
	for (int i = 0; i < data.size(); ++i)
	{
		if (i % (Width) == 0)
		{
			r++;
			_data.emplace_back(std::vector<int>(Width));
		}

		_data[r][i % Width] = data[i];
	}
}

std::vector<std::vector<int>> Properties::TileLayerProperties::GetData() const
{
	return _data;
}
