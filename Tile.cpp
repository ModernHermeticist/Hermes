#include "main.h"

Tile::Tile()
{
	blocks = false;
	walkable = false;
	explored = false;
}

Tile::Tile(int _xPos, int _yPos, int _sprite, TCODColor _foreground, TCODColor _background, bool _walkable, bool _blocks)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	foreground = _foreground;
	background = _background;
	walkable = _walkable;
	blocks = _blocks;
	explored = false;
}

Tile::Tile(int _xPos, int _yPos, int _sprite, TCODColor _foreground, TCODColor _background)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	foreground = _foreground;
	background = _background;
	walkable = true;
	blocks = false;
	explored = false;
}

Tile::~Tile()
{

}

int Tile::getXPos()
{
	return xPos;
}

int Tile::getYPos()
{
	return yPos;
}

bool Tile::getWalkable()
{
	return walkable;
}

bool Tile::getBlocks()
{
	return blocks;
}

bool Tile::getExplored()
{
	return explored;
}

int Tile::getSprite()
{
	return sprite;
}

TCODColor Tile::getForeground()
{
	return foreground;
}

TCODColor Tile::getBackground()
{
	return background;
}

void Tile::setWalkable(bool val)
{
	walkable = val;
}

void Tile::setBlocks(bool val)
{
	blocks = val;
}

void Tile::setExplored(bool val)
{
	explored = val;
}

void Tile::setSprite(int c)
{
	sprite = c;
}

void Tile::setForeground(TCODColor color)
{
	foreground = color;
}

void Tile::setBackground(TCODColor color)
{
	background = color;
}