#pragma once
#include "LayerBase.h"
#include "LayerProperties.h"
#include "Tile.h"
#include <memory>

struct ITextureManager;
struct IRenderer;

namespace Test
{
	class TileLayer :public LayerBase
	{
		ITextureManager&_textureManager;

		IRenderer& _renderer;

		LayerProperties _properties;

		std::vector<std::shared_ptr<Tile>>_tiles;

		Tileset*  FindTileset(int id);
	public:
		explicit TileLayer(const std::string& type, ITextureManager&textureManager, IRenderer&renderer);

		void GenerateTiles();

		void SetProperties(const LayerProperties& level_properties)
		{
			_properties = level_properties;
		}

		LayerProperties& Properties()
		{
			return _properties;
		}

		std::vector<Tile*> GetTiles();

		void Draw() override;
	};
}

