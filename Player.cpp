#include "main.h"

Player::Player(int _xPos, int _yPos, int _sprite)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
}

Player::~Player()
{

}

void Player::Update(TCOD_key_t key, Tile** tiles)
{
	int dX = 0;
	int dY = 0;
	if (key.vk == TCODK_KP4 && xPos > 0)
	{
		engine->addToLog("Trying to move west.");
		dX -= 1;
	}
	else if (key.vk == TCODK_KP6 && xPos < CELL_COLUMNS - 1)
	{
		engine->addToLog("Trying to move east.");
		dX += 1;
	}
	else if (key.vk == TCODK_KP8 && yPos > 0)
	{
		engine->addToLog("Trying to move north.");
		dY -= 1;
	}
	else if (key.vk == TCODK_KP2 && yPos < CELL_ROWS - 1)
	{
		engine->addToLog("Trying to move south.");
		dY += 1;
	}
	else if (key.vk == TCODK_KP1 && xPos > 0 && yPos < CELL_ROWS - 1)
	{
		engine->addToLog("Trying to move south-west.");
		dX -= 1;
		dY += 1;
	}
	else if (key.vk == TCODK_KP3 && xPos < CELL_COLUMNS - 1 && yPos < CELL_ROWS - 1)
	{
		engine->addToLog("Trying to move south-east.");
		dX += 1;
		dY += 1;
	}
	else if (key.vk == TCODK_KP7 && xPos > 0 && yPos > 0)
	{
		engine->addToLog("Trying to move north-west.");
		dX -= 1;
		dY -= 1;
	}
	else if (key.vk == TCODK_KP9 && xPos < CELL_COLUMNS - 1 && yPos > 0)
	{
		engine->addToLog("Trying to move north-east.");
		dX += 1;
		dY -= 1;
	}

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

int Player::getXPos()
{
	return xPos;
}

int Player::getYPos()
{
	return yPos;
}

int Player::getSprite()
{
	return sprite;
}

bool Player::canMoveTo(Tile tile, int newX, int newY)
{
	return (tile.getXPos() == newX && tile.getYPos() == newY) && (tile.getWalkable());
}