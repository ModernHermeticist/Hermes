#include "main.h"

Player::Player(int _xPos, int _yPos, int _sprite, int _maximumHealth)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	maximumHealth = _maximumHealth;
	currentHealth = _maximumHealth;
	alive = true;
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
		engine->addToLog("Trying to move west.", TCOD_blue);
		dX -= 1;
	}
	else if ((key.vk == TCODK_KP6 || key.vk == TCODK_RIGHT) && xPos < CELL_COLUMNS - 1)
	{
		engine->addToLog("Trying to move east.", TCOD_orange);
		dX += 1;
	}
	else if ((key.vk == TCODK_KP8 || key.vk == TCODK_UP) && yPos > 0)
	{
		engine->addToLog("Trying to move north.", TCOD_red);
		dY -= 1;
	}
	else if ((key.vk == TCODK_KP2 || key.vk == TCODK_DOWN) && yPos < CELL_ROWS - 1)
	{
		engine->addToLog("Trying to move south.", TCOD_purple);
		dY += 1;
	}
	else if (key.vk == TCODK_KP1 && xPos > 0 && yPos < CELL_ROWS - 1)
	{
		engine->addToLog("Trying to move south-west.", TCOD_yellow);
		dX -= 1;
		dY += 1;
	}
	else if (key.vk == TCODK_KP3 && xPos < CELL_COLUMNS - 1 && yPos < CELL_ROWS - 1)
	{
		engine->addToLog("Trying to move south-east.", TCOD_green);
		dX += 1;
		dY += 1;
	}
	else if (key.vk == TCODK_KP7 && xPos > 0 && yPos > 0)
	{
		engine->addToLog("Trying to move north-west.", TCOD_light_blue);
		dX -= 1;
		dY -= 1;
	}
	else if (key.vk == TCODK_KP9 && xPos < CELL_COLUMNS - 1 && yPos > 0)
	{
		engine->addToLog("Trying to move north-east.", TCOD_light_red);
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
			engine->setComputeFov(true);
			xPos += dX;
			yPos += dY;
			return;
		}
	}
}

int Player::getXPos() { return xPos; }

int Player::getYPos() { return yPos; }

void Player::setXPos(int val) { xPos = val; }
void Player::setYPos(int val) { yPos = val; }

int Player::getSprite() { return sprite; }

bool Player::canMoveTo(Tile tile, int newX, int newY)
{
	return (tile.getXPos() == newX && tile.getYPos() == newY) && (tile.getWalkable());
}

int Player::getCurrentHealth() { return currentHealth; }
int Player::getMaximumHealth() { return maximumHealth; }

void Player::setCurrentHealth(int val) { currentHealth = val; }
void Player::setMaximumHealtH(int val) { maximumHealth = val; }

void Player::takeDamage(int val)
{
	currentHealth -= val;
	if (currentHealth <= 0)
	{
		currentHealth = 0;
		alive = false;
	}
}
void Player::heal(int val)
{
	currentHealth += val;
	if (currentHealth > maximumHealth)
	{
		currentHealth = maximumHealth;
	}
}

TCODColor Player::getSpriteForeground() { return spriteForeground; }
TCODColor Player::getSpriteBackground() { return spriteBackground; }

void Player::setSprite(int s) { sprite = s; }
void Player::setSpriteForeground(TCODColor c) { spriteForeground = c; }
void Player::setSpriteBackground(TCODColor c) { spriteBackground = c; }