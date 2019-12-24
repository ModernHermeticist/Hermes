#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	Tile(int _xPos, int _yPos, int _sprite, TCODColor _foreground, TCODColor _background, bool _walkable, bool _blocks);
	Tile(int _xPos, int _yPos, int _sprite, TCODColor _foreground, TCODColor _background);
	~Tile();

	int getXPos();
	int getYPos();

	bool getWalkable();
	bool getBlocks();

	int getSprite();

	TCODColor getForeground();
	TCODColor getBackground();

	void setWalkable(bool val);
	void setBlocks(bool val);

	void setSprite(int c);

	void setForeground(TCODColor color);
	void setBackground(TCODColor color);

private:
	int xPos;
	int yPos;
	bool walkable;
	bool blocks;

	int sprite;

	TCODColor foreground;
	TCODColor background;
};


#endif
