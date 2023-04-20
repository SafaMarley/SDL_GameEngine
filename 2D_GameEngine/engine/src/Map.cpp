#include "Map.h"
#include "../../game/Game.h"
#include <fstream>

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char ch;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX;
	int srcY;

	const int srcW = 64;
	const int srcH = 64;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(ch);
			srcY = atoi(&ch) * srcH;
			mapFile.get(ch);
			srcX = atoi(&ch) * srcW;

			Game::AddTile(srcX, srcY, srcW, srcH, x * srcW, y * srcH);
			mapFile.ignore();
		}
	}

	mapFile.close();
}
