#ifndef PLAYER_H
#define PLAYER_H

class Engine;

class Player
{
public:
	Player(int _xPos, int _yPos, int _sprite, std::string _name, PlayerAI* _playerAI, 
		AttackComponent* _attackComponent, DestroyComponent* _destroyComponent, 
		InventoryComponent* _inventoryComponent, EquipmentComponent* _equipmentComponent);
	~Player();
	Engine::STATE Update();

	int getXPos();
	int getYPos();

	void setXPos(int val);
	void setYPos(int val);

	int getSprite();

	TCODColor getSpriteForeground();
	TCODColor getSpriteBackground();

	void setSprite(int s);
	void setSpriteForeground(TCODColor c);
	void setSpriteBackground(TCODColor c);

	std::string getName();
	void setName(std::string n);

	bool canMoveTo(Tile tile);

	void updatePosition(int dX, int dY);

	PlayerAI* getPlayerAI();
	DestroyComponent* getDestroyComponent();
	AttackComponent* getAttackComponent();
	InventoryComponent* getInventoryComponent();
	EquipmentComponent* getEquipmentComponent();

private:
	PlayerAI* playerAI;
	AttackComponent* attackComponent;
	DestroyComponent* destroyComponent;
	InventoryComponent* inventoryComponent;
	EquipmentComponent* equipmentComponent;

	int xPos;
	int yPos;

	int sprite;
	TCODColor spriteForeground;
	TCODColor spriteBackground;

	std::string name;

};

#endif