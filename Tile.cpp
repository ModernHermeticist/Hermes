#include "main.h"

Tile::Tile()
{
	xPos = 0;
	yPos = 0;
	sprite = ' ';
	blocks = false;
	walkable = false;
	explored = false;
	visibleForeground = TCOD_black;
	visibleBackground = TCOD_black;
	exploredForeground = TCOD_black;
	exploredBackground = TCOD_black;
}

Tile::Tile(int _xPos, int _yPos, int _sprite, TCODColor _foreground, TCODColor _background, bool _walkable, bool _blocks)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	visibleForeground = _foreground;
	visibleBackground = _background;
	exploredForeground = TCOD_darker_grey;
	exploredBackground = TCOD_black;
	walkable = _walkable;
	blocks = _blocks;
	explored = false;
}

Tile::Tile(int _xPos, int _yPos, int _sprite, TCODColor _foreground, TCODColor _background)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	visibleForeground = _foreground;
	visibleBackground = _background;
	exploredForeground = TCOD_darker_grey;
	exploredBackground = TCOD_black;
	walkable = true;
	blocks = false;
	explored = false;
}

Tile::~Tile(){}

int Tile::getXPos(){return xPos;}

int Tile::getYPos(){return yPos;}

bool Tile::getWalkable(){return walkable;}

bool Tile::getBlocks(){return blocks;}

bool Tile::getExplored(){return explored;}

int Tile::getSprite(){return sprite;}

TCODColor Tile::getVisibleForeground(){return visibleForeground;}

TCODColor Tile::getVisibleBackground(){return visibleBackground;}

TCODColor Tile::getExploredForeground(){return exploredForeground;}

TCODColor Tile::getExploredBackground(){return exploredBackground;}

void Tile::setWalkable(bool val){walkable = val;}

void Tile::setBlocks(bool val){blocks = val;}

void Tile::setExplored(bool val){explored = val;}

void Tile::setSprite(int c){sprite = c;}

void Tile::setVisibleForeground(TCODColor color){visibleForeground = color;}

void Tile::setVisibleBackground(TCODColor color){visibleBackground = color;}

void Tile::setExploredForeground(TCODColor color){exploredForeground = color;}

void Tile::setExploredBackground(TCODColor color){exploredBackground = color;}