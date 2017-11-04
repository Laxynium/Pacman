#include "Layer.h"
#include "JsonParser.h"
#include "Rect.h"
#include "IRenderer.h"


Test::Layer::Layer(ITextureManager& texureManager,IRenderer&renderer)
	:_textureManager(texureManager), _renderer(renderer)
{
}

vector<Tile*> Test::Layer::GetTiles() 
{
	vector<Tile*>vec;
	for(auto&el:_tiles)
	{
		vec.push_back(el.get());
	}
	return vec;
}

void Test::Layer::GenerateTiles()
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

			auto tile = make_shared<Tile>(d, s, tileset->Name);

			_tiles.push_back(move(tile));

		}
	}
		
}

Test::Tileset* Test::Layer::FindTileset(int id)
{
	for (auto&tileset : _properties._tilesets)
	{
		if(tileset.FirstGridId<=id&&id<=(tileset.FirstGridId+tileset.TileCount-1))
		{
			return &tileset;
		}
	}
	return nullptr;
}
void Test::Layer::Draw()
{
	for(auto&tile:_tiles)
	{
		auto&texture = _textureManager.FindTexture(tile->TextureName());
		Rect dRect = tile->DscRect();
		_renderer.CopyEx(texture, &tile->SrcRect(),&dRect);
		/*dRect.color = Color{ 255,255,0,0 };
		_renderer.DrawRect(dRect);*/
	}
}
