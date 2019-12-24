#include "main.h"

Player::Player(int _xPos, int _yPos)
{
	xPos = _xPos;
	yPos = _yPos;
}

Player::~Player()
{

}

void Player::Update(TCOD_key_t key, std::vector<Tile*> tiles)
{
	int dX = 0;
	int dY = 0;
	if (key.vk == TCODK_KP4 && xPos > 0)
	{
		dX -= 1;
	}
	else if (key.vk == TCODK_KP6 && xPos < CELL_COLUMNS - 1)
	{
		dX += 1;
	}
	else if (key.vk == TCODK_KP8 && yPos > 0)
	{
		dY -= 1;
	}
	else if (key.vk == TCODK_KP2 && yPos < CELL_ROWS - 1)
	{
		dY += 1;
	}
	else if (key.vk == TCODK_KP1 && xPos > 0 && yPos < CELL_ROWS - 1)
	{
		dX -= 1;
		dY += 1;
	}
	else if (key.vk == TCODK_KP3 && xPos < CELL_COLUMNS - 1 && yPos < CELL_ROWS - 1)
	{
		dX += 1;
		dY += 1;
	}
	else if (key.vk == TCODK_KP7 && xPos > 0 && yPos > 0)
	{
		dX -= 1;
		dY -= 1;
	}
	else if (key.vk == TCODK_KP9 && xPos < CELL_COLUMNS - 1 && yPos > 0)
	{
		dX += 1;
		dY -= 1;
	}

	if (dX != 0 || dY != 0)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			Tile* tile = tiles[i];
			int newX = dX + xPos;
			int newY = dY + yPos;

			if ((tile->getXPos() == newX && tile->getYPos() == newY) && (tile->getWalkable()))
			{
				xPos += dX;
				yPos += dY;
				return;
			}
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