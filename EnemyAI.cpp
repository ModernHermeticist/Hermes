#include "main.h"

EnemyAI::EnemyAI()
{
	moveCount = 0;
}
EnemyAI::~EnemyAI()
{

}

void EnemyAI::update(Entity* owner)
{
	moveOrAttack(owner, engine->getPlayer());
}

void EnemyAI::moveOrAttack(Entity* owner, Player* target)
{
	Tile** tiles = engine->getMap()->getWorld();

	int xPos = owner->getXPos();
	int yPos = owner->getYPos();

	int targetX = target->getXPos();
	int targetY = target->getYPos();

	if (engine->getMap()->isInFov(xPos, yPos))
	{
		moveCount = TRACKING_TURNS;
	}
	else moveCount--;

	if (moveCount > 0)
	{
		int dX = targetX - xPos;
		int dY = targetY - yPos;
		int stepDX = (dX > 0 ? 1 : -1);
		int stepDY = (dY > 0 ? 1 : -1);
		float distance = sqrtf(dX * dX + dY * dY);
		if (distance >= 2)
		{
			dX = (int)(round(dX / distance));
			dY = (int)(round(dY / distance));
			int newX = dX + xPos;
			int newY = dY + yPos;
			Tile* tile = &tiles[newX][newY];
			if (canMoveTo(tile, newX, newY))
			{
				owner->updatePosition(dX, dY);
			}
			else if (canMoveTo(&tiles[xPos + stepDX][yPos], xPos + stepDX, yPos))
			{
				owner->updatePosition(stepDX, 0);
			}
			else if (canMoveTo(&tiles[xPos][yPos + stepDY], xPos, yPos + stepDY))
			{
				owner->updatePosition(0, stepDY);
			}
		}
		else
		{
			AttackComponent* attackComponent = owner->getAttackComponent();
			int damage = attackComponent->getDamage();
			damage = target->getPlayerAI()->takeDamage(damage);
			engine->addToLog("You were hit by a " + owner->getName() + " for " + std::to_string(damage) + " damage!", TCOD_red);
			engine->setComputeFov(true);
		}
	}
}

std::vector<int> EnemyAI::takeDamage(Entity* owner, int val)
{
	DestroyComponent* destroyComponent = owner->getDestroyComponent();
	int damage = val - destroyComponent->getArmor();
	std::vector<int> retVal = { 0,0 };
	if (damage < 0) damage = 0;
	destroyComponent->adjustCurrentHealth(-damage);
	retVal[0] = damage;
	if (destroyComponent->getCurrentHealth() <= 0)
	{
		destroyComponent->die(owner);
		destroyComponent->setCurrentHealth(0);
		destroyComponent->setAlive(false);
		retVal[1] = -1;
		return retVal;
	}
	return retVal;
}
void EnemyAI::heal(Entity* owner, int val)
{
	DestroyComponent* destroyComponent = owner->getDestroyComponent();
	destroyComponent->adjustCurrentHealth(val);
	if (destroyComponent->getCurrentHealth() > destroyComponent->getMaximumHealth())
	{
		destroyComponent->setCurrentHealth(destroyComponent->getMaximumHealth());
	}
}

bool EnemyAI::canMoveTo(Tile* tile, int newX, int newY)
{
	std::vector<Entity*> entities = engine->getEntities();
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getXPos() == newX && entities[i]->getYPos() == newY && entities[i]->getDestroyComponent()->isAlive()) return false;
	}
	return tile->getWalkable();
}