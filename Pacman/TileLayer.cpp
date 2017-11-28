#include "TileLayer.h"
#include "ITextureManager.h"
#include "IRenderer.h"

Properties::TileLayer::TileLayer(const std::string& type,ITextureManager&textureManager,IRenderer&renderer, ICollisionManager&collisionManager):
LayerBase(type), _textureManager(textureManager), _renderer(renderer), _collisionManager(collisionManager)
{
}

std::vector<Tile*> Properties::TileLayer::GetTiles()
{
	std::vector<Tile*>vec;
	for (auto&el : _tiles)
	{
		vec.push_back(el.get());
	}
	return vec;
}

void Properties::TileLayer::GenerateTiles()
{
	auto data = _properties->GetData();

	for (int i = 0; i<data.size(); ++i)
	{
		for (int j = 0; j<data[i].size(); ++j)
		{
			const auto id = data[i][j];

			if (id == 0)
				continue;

			auto *tileset = FindTileset(id);

			if (tileset == nullptr)continue;


			const int unrelativePos = (id - tileset->FirstGridId);

			int w = tileset->TileWidth, h = tileset->TileHeight;

			int x = (unrelativePos % (tileset->Columns))*w;
			int y = (unrelativePos / (tileset->Columns))*h;

			Rect s{ x,y,w,h };
			Rect d{ j*w,i*h,w,h };

			auto tile = std::make_shared<Tile>(d, s, tileset->Name,_properties->Tag);

			_tiles.push_back(std::move(tile));

		}
	}

}

void Properties::TileLayer::SetProperties(const TileLayerProperties&& level_properties)
{
	_properties = std::make_unique<TileLayerProperties>(std::move(level_properties));
}

Properties::TileLayerProperties& Properties::TileLayer::Properties() const
{
	return *_properties;
}

Properties::Tileset* Properties::TileLayer::FindTileset(int id) const
{
	for (auto&tileset : _properties->tilesets())
	{
		if (tileset.FirstGridId <= id&&id <= (tileset.FirstGridId + tileset.TileCount - 1))
		{
			return &tileset;
		}
	}
	return nullptr;
}
void Properties::TileLayer::Draw()
{
	for (auto&tile : _tiles)
	{
		auto&texture = _textureManager.FindTexture(tile->TextureName());
		Rect dRect = tile->DscRect();
		_renderer.CopyEx(texture, &tile->SrcRect(), &dRect);
		/*dRect.color = Color{ 255,255,0,0 };
		_renderer.DrawRect(dRect);*/
	}
}

void Properties::TileLayer::Update()
{

}

Properties::TileLayer::~TileLayer()
{
	for (auto& collidable : _tiles)
	{
		_collisionManager.Deregister(*collidable);
	}
}
