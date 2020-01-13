#ifndef PLAYERAI_H
#define PLAYERAI_H

#include "Engine.h"

class PlayerAI
{
public:
	enum class movementDirection { WEST, EAST, NORTH, SOUTH, NORTHWEST, NORTHEAST, SOUTHWEST, SOUTHEAST };


	PlayerAI();
	~PlayerAI();

	Engine::STATE update();

	Engine::STATE parseKeyInput();

	Engine::STATE moveOrAttack(int dX, int dY, movementDirection dir);
	Engine::STATE pickUpItem();
	Engine::STATE dropItem(int c);
	Engine::STATE equipItem(int c);
	Engine::STATE useItem(int c);
	Engine::STATE inspectItem(int c);

	Engine::STATE gainExperience(int val);
	
	int getCharacterLevel();
	int getCurrentExperience();
	int getMaximumExperience();

	Engine::STATE progressCharacter();
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