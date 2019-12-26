#ifndef MAP_H
#define MAP_H

class Map
{
public:
	Map(int _width, int _height);
	~Map();

	Tile** getWorld();

	TCODMap* getTCODMap();

	void setTile(int x, int y, Tile tile);

	bool isInFov(int x, int y) const;
	bool isExplored(int x, int y) const;

	void computeFov();

private:
	int width;
	int height;

	Tile** world;

	TCODMap* map;

};

#endif