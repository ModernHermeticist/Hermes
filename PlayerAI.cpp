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
	if (dir == movementDirection::WEST) engine->addToLog("Trying to move west.", TCOD_blue);
	else if (dir == movementDirection::EAST) engine->addToLog("Trying to move east.", TCOD_orange);
	else if (dir == movementDirection::NORTH) engine->addToLog("Trying to move north.", TCOD_red);
	else if (dir == movementDirection::SOUTH) engine->addToLog("Trying to move south.", TCOD_purple);
	else if (dir == movementDirection::SOUTHWEST) engine->addToLog("Trying to move south-west.", TCOD_yellow);
	else if (dir == movementDirection::SOUTHEAST) engine->addToLog("Trying to move south-east.", TCOD_green);
	else if (dir == movementDirection::NORTHWEST) engine->addToLog("Trying to move north-west.", TCOD_light_blue);
	else if (dir == movementDirection::NORTHEAST) engine->addToLog("Trying to move north-east.", TCOD_light_red);


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
					enemy->takeDamage(destroyComponent, 1);
					engine->addToLog("You hit a thing for " + std::to_string(1) + " damage!", TCOD_red);
					engine->setComputeFov(true);
					return;
				}
			}
		}
		engine->setComputeFov(true);
		player->updatePosition(dX, dY);
		return;
	}
}

void PlayerAI::takeDamage(int val)
{
	Player* player = engine->getPlayer();
	DestroyComponent* destroyComponent = player->getDestroyComponent();
	destroyComponent->adjustCurrentHealth(-val);
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