#ifndef ENEMYAI_H
#define ENEMYAI_H

class EnemyAI
{
public:
	EnemyAI();
	~EnemyAI();

	void update();

	void moveOrAttack(AttackComponent* owner, DestroyComponent* target);

	void takeDamage(int val);
	void heal(int val);

private:

};

#endif
