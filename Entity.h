#ifndef ENTITY_H
#define ENTITY_H

class EnemyAI;

class Entity
{
public:
	enum xDirection { left = -1, right = 1};
	enum yDirection { up = -1, down = 1 };

	Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name, 
		EnemyAI* _enemyAI, AttackComponent* _attackComponent, DestroyComponent* _destroyComponent, 
		InventoryComponent* _inventoryComponent, ItemComponent* _itemComponent);
	~Entity();
	void Update();

	int getXPos();
	int getYPos();

	void setXPos(int val);
	void setYPos(int val);

	void updatePosition(int dX, int dY);

	int getSprite();
	void setSprite(int s);

	TCODColor getSpriteForeground();
	TCODColor getSpriteBackground();

	void setSpriteForeground(TCODColor c);
	void setSpriteBackground(TCODColor c);

	std::string getName();
	void setName(std::string n);

	EnemyAI* getEnemyAI();
	AttackComponent* getAttackComponent();
	DestroyComponent* getDestroyComponent();
	InventoryComponent* getInventoryComponent();
	ItemComponent* getItemComponent();


private:
	int xPos;
	int yPos;

	int sprite;

	TCODColor spriteForeground;
	TCODColor spriteBackground;

	std::string name;

	EnemyAI* enemyAI;
	AttackComponent* attackComponent;
	DestroyComponent* destroyComponent;
	InventoryComponent* inventoryComponent;
	ItemComponent* itemComponent;

};

#endif