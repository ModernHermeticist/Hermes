#include "main.h"

PlayerAI::PlayerAI()
{

}

PlayerAI::~PlayerAI()
{

}

void PlayerAI::update()
{
	parseKeyInput();
}

void PlayerAI::parseKeyInput()
{
	TCOD_key_t key = engine->getLastKey();

	switch (key.vk)
	{
		case TCODK_KP4:   moveOrAttack(-1, 0, movementDirection::WEST); break;
		case TCODK_LEFT:  moveOrAttack(-1, 0, movementDirection::WEST); break;
		case TCODK_KP6:   moveOrAttack(1, 0, movementDirection::EAST); break;
		case TCODK_RIGHT: moveOrAttack(1, 0, movementDirection::EAST); break;
		case TCODK_KP8:   moveOrAttack(0, -1, movementDirection::NORTH); break;
		case TCODK_UP:    moveOrAttack(0, -1, movementDirection::NORTH); break;
		case TCODK_KP2:   moveOrAttack(0, 1, movementDirection::SOUTH); break;
		case TCODK_DOWN:  moveOrAttack(0, 1, movementDirection::SOUTH); break;
		case TCODK_KP7:   moveOrAttack(-1, -1, movementDirection::NORTHWEST); break;
		case TCODK_KP9:   moveOrAttack(1, -1, movementDirection::NORTHEAST); break;
		case TCODK_KP1:   moveOrAttack(-1, 1, movementDirection::SOUTHWEST); break;
		case TCODK_KP3:   moveOrAttack(1, 1, movementDirection::SOUTHEAST); break;
		default: break;
	}
}

void PlayerAI::moveOrAttack(int dX, int dY, movementDirection dir)
{
	Player* player = engine->getPlayer();
	int xPos = player->getXPos();
	int yPos = player->getYPos();
	Tile** tiles = engine->getMap()->getWorld();
	int newX = dX + xPos;
	int newY = dY + yPos;
	Tile tile = tiles[newX][newY];


	if (player->canMoveTo(tile))
	{
		std::vector<Entity*> entities = engine->getEntities();
		int numOfEntities = entities.size();
		for (int i = 0; i < numOfEntities; i++)
		{
			Entity* entity = entities[i];
			EnemyAI* enemy = entity->getEnemyAI();
			DestroyComponent* destroyComponent = entity->getDestroyComponent();
			if (newX == entity->getXPos() && newY == entity->getYPos() && destroyComponent->isAlive())
			{
				if (destroyComponent != NULL)
				{
					AttackComponent* attackComponent = player->getAttackComponent();
					int damage = attackComponent->getDamage();
					engine->addToLog("You hit a " + entity->getName() + " for " + std::to_string(damage) + " damage!", TCOD_red);
					enemy->takeDamage(entity, damage);
					engine->setComputeFov(true);
					return;
				}
			}
		}
		engine->setComputeFov(true);
		player->updatePosition(dX, dY);
		return;
	}
	else
	{
		engine->addToLog("You cannot move there.", TCOD_grey);
	}
}

void PlayerAI::takeDamage(int val)
{
	Player* player = engine->getPlayer();
	DestroyComponent* destroyComponent = player->getDestroyComponent();
	int damage = val - destroyComponent->getArmor();
	if (damage < 0) damage = 0;
	destroyComponent->adjustCurrentHealth(-damage);
	if (destroyComponent->getCurrentHealth() <= 0)
	{
		destroyComponent->setCurrentHealth(0);
		destroyComponent->setAlive(false);
	}
}
void PlayerAI::heal(int val)
{
	Player* player = engine->getPlayer();
	DestroyComponent* destroyComponent = player->getDestroyComponent();
	destroyComponent->adjustCurrentHealth(val);
	if (destroyComponent->getCurrentHealth() > destroyComponent->getMaximumHealth())
	{
		destroyComponent->setCurrentHealth(destroyComponent->getMaximumHealth());
	}
}