#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(int _xPos, int _yPos, int _sprite, PlayerAI* _playerAI, AttackComponent* _attackComponent, DestroyComponent* _destroyComponent);
	~Player();
	void Update();

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

private:
	PlayerAI* playerAI;
	AttackComponent* attackComponent;
	DestroyComponent* destroyComponent;

	int xPos;
	int yPos;

	int sprite;
	TCODColor spriteForeground;
	TCODColor spriteBackground;

	std::string name;

};

#endif