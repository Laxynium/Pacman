#include "TileLayer.h"
#include "ITextureManager.h"
#include "IRenderer.h"

Test::TileLayer::TileLayer(const std::string& type,ITextureManager&textureManager,IRenderer&renderer):
LayerBase(type), _textureManager(textureManager), _renderer(renderer)
{
}

std::vector<Tile*> Test::TileLayer::GetTiles()
{
	std::vector<Tile*>vec;
	for (auto&el : _tiles)
	{
		vec.push_back(el.get());
	}
	return vec;
}

void Test::TileLayer::GenerateTiles()
{
	auto data = _properties.GetData();

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

			auto tile = std::make_shared<Tile>(d, s, tileset->Name);

			_tiles.push_back(std::move(tile));

		}
	}

}

Test::Tileset* Test::TileLayer::FindTileset(int id)
{
	for (auto&tileset : _properties.Tilesets())
	{
		if (tileset.FirstGridId <= id&&id <= (tileset.FirstGridId + tileset.TileCount - 1))
		{
			return &tileset;
		}
	}
	return nullptr;
}
void Test::TileLayer::Draw()
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