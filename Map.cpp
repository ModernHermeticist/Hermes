#include "main.h"

Map::Map(int _width, int _height)
{
	width = _width;
	height = _height;
	world = new Tile * [width];
	for (int i = 0; i < width; i++)
	{
		world[i] = new Tile[height];
	}
	map = new TCODMap(width, height);
}

Map::~Map()
{
	for (int i = 0; i < width; i++)
	{
		delete[] world[i];
	}
	delete[] world;
	delete map;
}


Tile** Map::getWorld() { return world; }

void Map::setTile(int x, int y, Tile tile)
{
	world[x][y] = tile;
}

bool Map::isExplored(int x, int y) const
{
	return world[x][y].getExplored();
}

bool Map::isInFov(int x, int y) const
{
	if (map->isInFov(x, y))
	{
		world[x][y].setExplored(true);
		return true;
	}
	return false;
}

void Map::computeFov()
{
	map->computeFov(engine->getPlayer()->getXPos(), engine->getPlayer()->getYPos(), engine->getFovRadius());
}

TCODMap* Map::getTCODMap() { return map; }