#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	Tile();
	Tile(int _xPos, int _yPos, int _sprite, TCODColor _foreground, TCODColor _background, bool _walkable, bool _blocks);
	Tile(int _xPos, int _yPos, int _sprite, TCODColor _foreground, TCODColor _background);
	~Tile();

	int getXPos();
	int getYPos();

	bool getWalkable();
	bool getBlocks();

	bool getExplored();

	int getSprite();

	TCODColor getVisibleForeground();
	TCODColor getVisibleBackground();
	TCODColor getExploredForeground();
	TCODColor getExploredBackground();

	void setWalkable(bool val);
	void setBlocks(bool val);

	void setExplored(bool val);

	void setSprite(int c);

	void setVisibleForeground(TCODColor color);
	void setVisibleBackground(TCODColor color);
	void setExploredForeground(TCODColor color);
	void setExploredBackground(TCODColor color);

private:
	int xPos;
	int yPos;
	bool walkable;
	bool blocks;
	bool explored;

	int sprite;

	TCODColor visibleForeground;
	TCODColor visibleBackground;

	TCODColor exploredForeground;
	TCODColor exploredBackground;
};


#endif
