#ifndef PLAYERAI_H
#define PLAYERAI_H

class PlayerAI
{
public:
	enum movementDirection{ WEST,EAST,NORTH,SOUTH,NORTHWEST,NORTHEAST,SOUTHWEST,SOUTHEAST };
	PlayerAI();
	~PlayerAI();

	void update();

	void parseKeyInput();

	void moveOrAttack(int dX, int dY, movementDirection dir);

	void takeDamage(int val);
	void heal(int val);

private:



};

#endif