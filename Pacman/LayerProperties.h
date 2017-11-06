#pragma once
#include "Tileset.h"
#include <vector>
namespace Test
{
	class LayerProperties
	{
		friend class Layer;

		std::vector<std::vector<int>> _data;

		std::vector<Test::Tileset> _tilesets;

	public:

		std::vector<Test::Tileset>& Tilesets() 
		{
			return _tilesets;
		}

		void SetTilesets(const std::vector<Test::Tileset>& tilesets)
		{
			_tilesets = tilesets;
		}

		void SetData(const std::vector<int>&data)
		{
			int r = -1;
			for (int i = 0; i<data.size(); ++i)
			{
				if (i % (Width) == 0)
				{
					r++;
					_data.emplace_back(std::vector<int>(Width));
				}

				_data[r][i%Width] = data[i];
			}
		}

		std::vector<std::vector<int>>GetData()const
		{
			return _data;
		}

		std::string Name;

		int Width;

		int Height;

		int X;

		int Y;

		bool IsCollidable;

	};
}


