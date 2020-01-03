#include "main.h"

Entity::Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	spriteForeground = _spriteForeground;
	spriteBackground = _spriteBackground;
	name = _name;
	enemyAI = NULL;
	attackComponent = NULL;
	destroyComponent = NULL;
	inventoryComponent = NULL;
	itemComponent = NULL;
}

Entity::Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name,
	EnemyAI* _enemyAI, AttackComponent* _attackComponent, DestroyComponent* _destroyComponent, 
	InventoryComponent* _inventoryComponent, ItemComponent* _itemComponent)
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
	inventoryComponent = _inventoryComponent;
	itemComponent = _itemComponent;
}

Entity::Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name,
	std::string _description, ItemComponent* _itemComponent)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	spriteForeground = _spriteForeground;
	spriteBackground = _spriteBackground;
	name = _name;
	description = _description;
	enemyAI = NULL;
	attackComponent = NULL;
	destroyComponent = NULL;
	inventoryComponent = NULL;
	itemComponent = _itemComponent;
}

Entity::Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name, std::string _description,
	EnemyAI* _enemyAI, AttackComponent* _attackComponent, DestroyComponent* _destroyComponent,
	InventoryComponent* _inventoryComponent, ItemComponent* _itemComponent)
{
	xPos = _xPos;
	yPos = _yPos;
	sprite = _sprite;
	spriteForeground = _spriteForeground;
	spriteBackground = _spriteBackground;
	name = _name;
	description = _description;
	enemyAI = _enemyAI;
	attackComponent = _attackComponent;
	destroyComponent = _destroyComponent;
	inventoryComponent = _inventoryComponent;
	itemComponent = _itemComponent;
}

Entity::~Entity()
{
	if (enemyAI != NULL) delete enemyAI;
	if (attackComponent != NULL) delete attackComponent;
	if (destroyComponent != NULL) delete destroyComponent;
	if (itemComponent != NULL) delete itemComponent;
	if (inventoryComponent != NULL) delete inventoryComponent;
};

void Entity::Update()
{
	if (this->getItemComponent() != NULL) { return; }
	if (!this->destroyComponent->isAlive()) { return; }
	if (enemyAI != NULL) enemyAI->update(this);
}

int Entity::getXPos() { return xPos; }
int Entity::getYPos() { return yPos; }

void Entity::setXPos(int val) { xPos = val; }
void Entity::setYPos(int val) { yPos = val; }

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

std::string Entity::getDescription() { return description; }

EnemyAI* Entity::getEnemyAI() { return enemyAI; }
AttackComponent* Entity::getAttackComponent() { return attackComponent; }
DestroyComponent* Entity::getDestroyComponent() { return destroyComponent; }
InventoryComponent* Entity::getInventoryComponent() { return inventoryComponent; }
ItemComponent* Entity::getItemComponent() { return itemComponent; }
