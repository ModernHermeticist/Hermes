#include "main.h"

Entity::Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	spriteForeground = _spriteForeground;
	spriteBackground = _spriteBackground;
}

Entity::~Entity() {};

void Entity::Update(Tile** tiles)
{
	int dX = rand() % 3;
	int dY = rand() % 3;
	if (dX == 1) dX = xDirection::left;
	else if (dX == 2) dX = xDirection::right;

	if (dY == 1) dY = yDirection::up;
	else if (dY == 2) dY = yDirection::down;



	if (dX != 0 || dY != 0)
	{
		int newX = dX + xPos;
		int newY = dY + yPos;
		Tile tile = tiles[newX][newY];
		if (canMoveTo(tile, newX, newY))
		{
			xPos += dX;
			yPos += dY;
			return;
		}
	}
}

int Entity::getXPos() { return xPos; }
int Entity::getYPos() { return yPos; }

int Entity::getSprite() { return sprite; }

TCODColor Entity::getSpriteForeground()
{
	return spriteForeground;
}

TCODColor Entity::getSpriteBackground()
{
	return spriteBackground;
}

void Entity::setSpriteForeground(TCODColor c)
{
	spriteForeground = c;
}
void Entity::setSpriteBackground(TCODColor c)
{
	spriteBackground = c;
}


bool Entity::canMoveTo(Tile tile, int newX, int newY)
{
	std::vector<Entity*> entities = engine->getEntities();
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getXPos() == newX && entities[i]->getYPos() == newY) return false;
	}
	return (newX > 0 && newY > 0 && newX < CELL_COLUMNS - 1 && newY < CELL_ROWS - 1 &&
		tile.getXPos() == newX && tile.getYPos() == newY) && (tile.getWalkable());
}