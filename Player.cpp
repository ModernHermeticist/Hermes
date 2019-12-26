#include "main.h"

Player::Player(int _xPos, int _yPos, int _sprite, int _maximumHealth)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	maximumHealth = _maximumHealth;
	currentHealth = _maximumHealth;
	playerAI = new PlayerAI();
	alive = true;
}

Player::~Player()
{
	delete playerAI;
}

void Player::Update()
{
	playerAI->update();
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

void Player::adjustCurrentHealth(int val) { currentHealth += val; }

void Player::setCurrentHealth(int val) { currentHealth = val; }
void Player::setMaximumHealtH(int val) { maximumHealth = val; }

TCODColor Player::getSpriteForeground() { return spriteForeground; }
TCODColor Player::getSpriteBackground() { return spriteBackground; }

void Player::setSprite(int s) { sprite = s; }
void Player::setSpriteForeground(TCODColor c) { spriteForeground = c; }
void Player::setSpriteBackground(TCODColor c) { spriteBackground = c; }

bool Player::isAlive() { return alive; }
void Player::setAlive(bool val) { alive = val; }

void Player::updatePosition(int dX, int dY)
{
	xPos += dX;
	yPos += dY;
}