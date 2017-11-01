#include "Layer.h"
#include <fstream>
#include "JsonParser.h"
#include "Rect.h"
#include "IRenderer.h"

//TODO fix bugs related with multi tileset source
//TODO add cache becouse layer is static

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

	//TODO here is bug

	for (int i = 0; i<data.size(); ++i)
		for (int j = 0; j<data[i].size(); ++j)
		{
			const auto el = data[i][j];

			if (el == 0)
				continue;

			//TODO fix bug here, becouse its work if there is only one tileset
			for (auto&tileset : _properties._tilesets)
			{
				const int unrelativePos = (el - tileset.FirstGridId);

				int w = tileset.TileWidth, h = tileset.TileHeight;

				int x = (unrelativePos % (tileset.Columns))*w;
				int y = (unrelativePos / (tileset.Columns))*h;

				Rect s{ x,y,w,h };
				Rect d{ j*w,i*h,w,h};//minus 2 to make collision less restrict
				//TODO fix bug
				auto tile = make_shared<Tile>(d);
				_tiles.push_back(move(tile));
			}
		}
}
void Test::Layer::Draw()
{
	auto data = _properties.GetData();

	//TODO here is bug
	
	for (int i = 0; i<data.size(); ++i)
		for (int j = 0; j<data[i].size(); ++j)
		{
			auto el = data[i][j];

			if (el == 0)
				continue;

			//TODO fix bug here, becouse its work if there is only one tileset
			//TODO cache tiles becouse they don't change
			for (auto&tileset : _properties._tilesets)
			{
				int unrelativePos = (el - tileset.FirstGridId);

				int w = tileset.TileWidth, h = tileset.TileHeight;

				int x = (unrelativePos % (tileset.Columns))*w;
				int y = (unrelativePos / (tileset.Columns))*h;

				Rect s{ x,y,w,h };
				Rect d{ j*w,i*h,w,h };
				//TODO fix bug
				auto &texture = _textureManager.FindTexture(tileset.Name);
				_renderer.CopyEx(texture, &s, &d);
				//TODO remove,for testing purpose
				d.color = Color{ 255,255,0,0 };
				_renderer.DrawRect(d);
			}
		}
}
