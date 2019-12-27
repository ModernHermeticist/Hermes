#ifndef ENEMYAI_H
#define ENEMYAI_H

class Entity;
class Player;
static const int TRACKING_TURNS = 3;

class EnemyAI
{
public:
	EnemyAI();
	~EnemyAI();

	void update(Entity* owner);

	void moveOrAttack(Entity* owner, Player* target);

	void takeDamage(DestroyComponent* owner, int val);
	void heal(DestroyComponent* owner, int val);

	bool canMoveTo(Tile* tile, int newX, int newY);

private:
	int moveCount;

};

#endif
