#include "main.h"


Player::Player(int _xPos, int _yPos, int _sprite, PlayerAI* _playerAI, AttackComponent* _attackComponent, DestroyComponent* _destroyComponent)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	playerAI = _playerAI;
	attackComponent = _attackComponent;
	destroyComponent = _destroyComponent;
}

Player::~Player()
{
	delete playerAI;
	delete attackComponent;
	delete destroyComponent;
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

bool Player::canMoveTo(Tile tile){return tile.getWalkable();}

TCODColor Player::getSpriteForeground() { return spriteForeground; }
TCODColor Player::getSpriteBackground() { return spriteBackground; }

void Player::setSprite(int s) { sprite = s; }
void Player::setSpriteForeground(TCODColor c) { spriteForeground = c; }
void Player::setSpriteBackground(TCODColor c) { spriteBackground = c; }

std::string Player::getName() { return name; }
void Player::setName(std::string n) { name = n; }

void Player::updatePosition(int dX, int dY)
{
	xPos += dX;
	yPos += dY;
}
PlayerAI* Player::getPlayerAI() { return playerAI; }
AttackComponent* Player::getAttackComponent() { return attackComponent; }
DestroyComponent* Player::getDestroyComponent() { return destroyComponent; }