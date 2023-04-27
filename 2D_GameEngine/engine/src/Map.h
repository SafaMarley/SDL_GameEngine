#pragma once
#include <string>

class Map
{
public:
	Map(const char *mapPath);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);

private:
	const char *mapFilePath;
	int mapScale;
	int tileSize;
};

