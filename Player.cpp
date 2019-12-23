#include "main.h"

Player::Player(int _xPos, int _yPos)
{
	xPos = _xPos;
	yPos = _yPos;
}

Player::~Player()
{

}

void Player::Update(TCOD_key_t key)
{
	if ((key.vk == TCODK_KP4 || key.vk == TCODK_LEFT) && xPos > 0)
	{
		xPos -= 1;
	}
	else if ((key.vk == TCODK_KP6 || key.vk == TCODK_RIGHT) && xPos < CELL_COLUMNS - 1)
	{
		xPos += 1;
	}
	else if ((key.vk == TCODK_KP8 || key.vk == TCODK_UP) && yPos > 0)
	{
		yPos -= 1;
	}
	else if ((key.vk == TCODK_KP2 || key.vk == TCODK_DOWN) && yPos < CELL_ROWS - 1)
	{
		yPos += 1;
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