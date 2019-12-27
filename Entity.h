#ifndef ENTITY_H
#define ENTITY_H

class EnemyAI;

class Entity
{
public:
	enum xDirection { left = -1, right = 1};
	enum yDirection { up = -1, down = 1 };

	Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground, EnemyAI* _enemyAI, AttackComponent* _attackComponent, DestroyComponent* destroyComponent);
	~Entity();
	void Update();

	int getXPos();
	int getYPos();

	void updatePosition(int dX, int dY);

	int getSprite();

	TCODColor getSpriteForeground();
	TCODColor getSpriteBackground();

	void setSpriteForeground(TCODColor c);
	void setSpriteBackground(TCODColor c);

	EnemyAI* getEnemyAI();
	AttackComponent* getAttackComponent();
	DestroyComponent* getDestroyComponent();


private:
	int xPos;
	int yPos;

	int sprite;

	bool dead;

	TCODColor spriteForeground;
	TCODColor spriteBackground;

	EnemyAI* enemyAI;
	AttackComponent* attackComponent;
	DestroyComponent* destroyComponent;

};

#endif