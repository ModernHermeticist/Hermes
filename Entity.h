#ifndef ENTITY_H
#define ENTITY_H

class EnemyAI;

class Entity
{
public:
	enum xDirection { left = -1, right = 1};
	enum yDirection { up = -1, down = 1 };

	Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name);
	Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name, AnimatorComponent* _animatorComponent);
	Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name,
		EnemyAI* _enemyAI, AttackComponent* _attackComponent, DestroyComponent* _destroyComponent, AnimatorComponent* _animatorComponent);
	Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name, 
		EnemyAI* _enemyAI, AttackComponent* _attackComponent, DestroyComponent* _destroyComponent, 
		InventoryComponent* _inventoryComponent, ItemComponent* _itemComponent);
	Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name,
		std::string _description, ItemComponent* _itemComponent);
	Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, std::string _name, std::string _description,
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
	TCODColor getStoreForeground();
	TCODColor getStoreBackground();

	void setSpriteForeground(TCODColor c);
	void setSpriteBackground(TCODColor c);
	void setStoreForeground(TCODColor color);
	void setStoreBackground(TCODColor color);

	std::string getName();
	void setName(std::string n);
	std::string getDescription();

	EnemyAI* getEnemyAI();
	AttackComponent* getAttackComponent();
	DestroyComponent* getDestroyComponent();
	InventoryComponent* getInventoryComponent();
	ItemComponent* getItemComponent();
	AnimatorComponent* getAnimatorComponent();

	void destroyAnimatorComponent();


private:
	int xPos;
	int yPos;

	int sprite;

	TCODColor spriteForeground;
	TCODColor spriteBackground;

	TCODColor storeForeground;
	TCODColor storeBackground;

	std::string name;
	std::string description;

	EnemyAI* enemyAI;
	AttackComponent* attackComponent;
	DestroyComponent* destroyComponent;
	InventoryComponent* inventoryComponent;
	ItemComponent* itemComponent;
	AnimatorComponent* animatorComponent;

};

#endif