#include "Map.h"
#include "../../game/Game.h"
#include <fstream>
#include "../ecs/ECS.h"
#include "../ecs/Components.h"

extern Manager manager;

Map::Map(const char *mapPath) : mapFilePath(mapPath)
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

			AddTile(srcX, srcY, srcW, srcH, x * srcW, y * srcH);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(ch);
			if (ch == '1')
			{
				auto& tileCollider(manager.addEntity());
				tileCollider.addComponent<ColliderComponent>("terrain", x * srcW, y * srcH, srcW, srcH);
				tileCollider.addGroup(Game::groupColliders);
			}

			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int srcW, int srcH, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, srcW, srcH, xPos, yPos, mapFilePath);
	tile.addGroup(Game::groupMap);
}
