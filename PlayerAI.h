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
	void useItem(int c);
	void inspectItem(int c);

	void gainExperience(int val);
	
	int getCharacterLevel();
	int getCurrentExperience();
	int getMaximumExperience();

	void progressCharacter();
	void recalculateStats();
	void applyStatPoints(std::vector<int> statSelections);

	void modifyStatsOnItemEquip(ItemComponent* item);
	void modifyStatsOnItemDeEquip(ItemComponent* item);

	void selectTarget();

	int takeDamage(int val);
	void heal(int val);

	Entity* getTarget();
	void setTarget(Entity* newTarget);

private:
	int availableStatPoints = 0;

	int characterLevel;
	int currentExperience;
	int maximumExperience;

	Entity* target;


};

#endif