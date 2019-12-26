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
	int xPos = engine->getPlayer()->getXPos();
	int yPos = engine->getPlayer()->getYPos();
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


	if (engine->getPlayer()->canMoveTo(tile, newX, newY))
	{
		engine->setComputeFov(true);
		engine->getPlayer()->updatePosition(dX, dY);
		return;
	}
	std::vector<Entity*> entities = engine->getEntities();
	int numOfEntities = entities.size();
}

void PlayerAI::takeDamage(int val)
{
	Player* player = engine->getPlayer();
	player->adjustCurrentHealth(-val);
	if (player->getCurrentHealth() <= 0)
	{
		player->setCurrentHealth(0);
		player->setAlive(false);
	}
}
void PlayerAI::heal(int val)
{
	Player* player = engine->getPlayer();
	player->adjustCurrentHealth(val);
	if (player->getCurrentHealth() > player->getMaximumHealth())
	{
		player->setCurrentHealth(player->getMaximumHealth());
	}
}