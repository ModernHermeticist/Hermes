#ifndef PLAYERAI_H
#define PLAYERAI_H

class PlayerAI
{
public:
	enum class movementDirection { WEST, EAST, NORTH, SOUTH, NORTHWEST, NORTHEAST, SOUTHWEST, SOUTHEAST };


	PlayerAI();
	~PlayerAI();

	void update();

	void parseKeyInput();

	void moveOrAttack(int dX, int dY, movementDirection dir);
	void pickUpItem();
	void dropItem(int c);
	void equipItem(int c);

	void gainExperience(int val);
	
	int getCharacterLevel();
	int getCurrentExperience();
	int getMaximumExperience();

	void progressCharacter();

	void modifyStatsOnItemEquip(ItemComponent* item);
	void modifyStatsOnItemDeEquip(ItemComponent* item);

	int takeDamage(int val);
	void heal(int val);

private:
	int characterLevel;
	int currentExperience;
	int maximumExperience;


};

#endif