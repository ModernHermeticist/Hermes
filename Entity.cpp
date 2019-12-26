#include "main.h"

Entity::Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	spriteForeground = _spriteForeground;
	spriteBackground = _spriteBackground;
	alive = true;
	moveCount = 0;
}

Entity::~Entity() {};

void Entity::Update(Tile** tiles, int targetX, int targetY)
{
	if (!alive) { return; }
	if (engine->getMap()->isInFov(xPos, yPos))
	{
		moveCount = TRACKING_TURNS;
	}
	else moveCount--;

	if (moveCount > 0)
	{
		int dX = targetX - xPos;
		int dY = targetY - yPos;
		int stepDX = (dX > 0 ? 1 : -1);
		int stepDY = (dY > 0 ? 1 : -1);
		float distance = sqrtf(dX * dX + dY * dY);
		if (distance >= 2)
		{
			dX = (int)(round(dX / distance));
			dY = (int)(round(dY / distance));
			int newX = dX + xPos;
			int newY = dY + yPos;
			Tile tile = tiles[newX][newY];
			if (canMoveTo(tile, newX, newY))
			{
				xPos += dX;
				yPos += dY;
			}
			else if (canMoveTo(tiles[xPos + stepDX][yPos], xPos + stepDX, yPos))
			{
				xPos += stepDX;
			}
			else if (canMoveTo(tiles[xPos][yPos + stepDY], xPos, yPos + stepDY))
			{
				yPos += stepDY;
			}
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