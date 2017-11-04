#pragma once
#include <string>
#include <vector>
#include "Tileset.h"
#include "IDrawable.h"
#include "ITextureManager.h"
#include "IRenderer.h"
#include "LayerProperties.h"
#include "Tile.h"
#include <memory>

using namespace std;
namespace Test
{
	class Layer:public IDrawable
	{	
		ITextureManager&_textureManager;

		IRenderer& _renderer;

		LayerProperties _properties;

		std::vector<shared_ptr<Tile>>_tiles;

		Tileset*  FindTileset(int id);

	public:
		void GenerateTiles();

		void SetProperties(const LayerProperties& level_properties)
		{
			_properties = level_properties;
		}

		LayerProperties& Properties() 
		{
			return _properties;
		}

		Layer(ITextureManager&texureManager, IRenderer&renderer);

		vector<Tile*> GetTiles();

		void Draw() override;	
	};
}
