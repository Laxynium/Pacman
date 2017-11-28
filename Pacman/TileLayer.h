#pragma once
#include "LayerBase.h"
#include "TileLayerProperties.h"
#include "Tile.h"
#include <memory>
#include "ICollisionManager.h"

struct ITextureManager;
struct IRenderer;

namespace Properties
{
	class TileLayer :public LayerBase
	{
		ITextureManager&_textureManager;

		IRenderer& _renderer;

		std::unique_ptr<TileLayerProperties> _properties;

		std::vector<std::shared_ptr<Tile>>_tiles;

		ICollisionManager& _collisionManager;

		Tileset*  FindTileset(int id) const;
	public:
		explicit TileLayer(const std::string& type, ITextureManager&textureManager, IRenderer&renderer,ICollisionManager&collisionManager);

		void GenerateTiles();

		void SetProperties(const TileLayerProperties&& level_properties);

		TileLayerProperties& Properties() const;

		std::vector<Tile*> GetTiles();

		void Draw() override;

		void Update() override;

		virtual ~TileLayer();
	};
}

