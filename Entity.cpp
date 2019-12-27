#include "main.h"


Entity::Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name,
	EnemyAI* _enemyAI, AttackComponent* _attackComponent, DestroyComponent* _destroyComponent)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	spriteForeground = _spriteForeground;
	spriteBackground = _spriteBackground;
	name = _name;
	enemyAI = _enemyAI;
	attackComponent = _attackComponent;
	destroyComponent = _destroyComponent;
}

Entity::~Entity()
{
	if (enemyAI != NULL) delete enemyAI;
	if (attackComponent != NULL) delete attackComponent;
	if (destroyComponent != NULL) delete destroyComponent;
};

void Entity::Update()
{
	if (!this->destroyComponent->isAlive()) { return; }
	if (enemyAI != NULL) enemyAI->update(this);
}

int Entity::getXPos() { return xPos; }
int Entity::getYPos() { return yPos; }

void Entity::updatePosition(int dX, int dY)
{
	xPos += dX;
	yPos += dY;
}

int Entity::getSprite() { return sprite; }
void Entity::setSprite(int s) { sprite = s; }

TCODColor Entity::getSpriteForeground(){return spriteForeground;}

TCODColor Entity::getSpriteBackground(){return spriteBackground;}

void Entity::setSpriteForeground(TCODColor c){spriteForeground = c;}

void Entity::setSpriteBackground(TCODColor c){spriteBackground = c;}

std::string Entity::getName() { return name; }
void Entity::setName(std::string n) { name = n; }

EnemyAI* Entity::getEnemyAI() { return enemyAI; }
AttackComponent* Entity::getAttackComponent() { return attackComponent; }
DestroyComponent* Entity::getDestroyComponent() { return destroyComponent; }
