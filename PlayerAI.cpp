#include "main.h"

PlayerAI::PlayerAI()
{
	characterLevel = 1;
	currentExperience = 0;
	maximumExperience = 10;
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


	switch (key.c)
	{
		case 'c':
		{
			engine->setState(Engine::STATE::SHOW_CHARACTER_SCREEN);
			TCODConsole::root->clear();
			drawCharacterWindow();
			TCODConsole::flush();
			break;
		}
		case 'g':
		{
			pickUpItem();
			break;
		}
		case 'i':
		{
			engine->setState(Engine::STATE::SHOW_INVENTORY_SCREEN);
			TCODConsole::root->clear();
			drawInventoryWindow();
			TCODConsole::flush();
			break;
		}


		default: break;
	}
}

void PlayerAI::pickUpItem()
{
	std::vector<Entity*> entities = engine->getEntities();
	Player* player = engine->getPlayer();
	InventoryComponent* inventoryComponent = player->getInventoryComponent();
	int xPos = player->getXPos();
	int yPos = player->getYPos();
	engine->setRefresh(true);
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* entity = *it;
		ItemComponent* itemComponent = entity->getItemComponent();
		if (itemComponent != NULL && entity->getXPos() == xPos && entity->getYPos() == yPos)
		{
			if (inventoryComponent->getCurrentStorageSize() == inventoryComponent->getStorageCapacity())
			{
				engine->addToLog("Inventory is full.", TCOD_grey);
				return;
			}
			else
			{
				inventoryComponent->addToStorage(entity);
				engine->removeEntity(entity);
				engine->addToLog("You pick up a " + entity->getName(), TCOD_grey);
				return;
			}
		}
	}
	engine->addToLog("There is nothing here to pick up.", TCOD_grey);
}

void PlayerAI::dropItem(int c)
{
	Player* player = engine->getPlayer();
	InventoryComponent* inventoryComponent = player->getInventoryComponent();
	Entity* entity = inventoryComponent->getItemAtLocation(c);
	inventoryComponent->removeFromStorage(entity);
	engine->addEntity(entity);
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
	engine->setRefresh(true);

	if (player->canMoveTo(tile))
	{
		std::vector<Entity*> entities = engine->getEntities();
		int numOfEntities = entities.size();
		for (int i = 0; i < numOfEntities; i++)
		{
			Entity* entity = entities[i];
			EnemyAI* enemy = entity->getEnemyAI();
			DestroyComponent* destroyComponent = entity->getDestroyComponent();
			ItemComponent* itemComponent = entity->getItemComponent();
			if (destroyComponent == NULL && itemComponent != NULL)
			{
				break;
			}
			if (newX == entity->getXPos() && newY == entity->getYPos() && destroyComponent->isAlive())
			{
				AttackComponent* attackComponent = player->getAttackComponent();
				int damage = attackComponent->getDamage();
				std::vector<int> retVal = enemy->takeDamage(entity, damage);
				damage = retVal[0];
				engine->addToLog("You hit a " + entity->getName() + " for " + std::to_string(damage) + " damage!", TCOD_red);
				if (retVal[1] == -1)
				{
					engine->addToLog(entity->getName() + " dies!", TCOD_darker_red);
					gainExperience(destroyComponent->getExperienceValue());
				}
				engine->setComputeFov(true);
				return;
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

void PlayerAI::gainExperience(int val)
{
	currentExperience += val; 
	engine->addToLog("You gain " + std::to_string(val) + " experience!", TCOD_gold);
	if (currentExperience >= maximumExperience)
	{
		progressCharacter();
	}
}

int PlayerAI::getCharacterLevel() { return characterLevel; }
int PlayerAI::getCurrentExperience() { return currentExperience; }
int PlayerAI::getMaximumExperience() { return maximumExperience; }

void PlayerAI::progressCharacter()
{
	currentExperience = 0;
	maximumExperience = round(maximumExperience * 1.5);
	characterLevel += 1;
	engine->addToLog("You have attained level " + std::to_string(characterLevel) + "!", TCOD_gold);
	/*TODO*/ 
	/*
	Stuff for character progression.
	Increase stats, increase attributes... etc.
	*/
}

int PlayerAI::takeDamage(int val)
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
	return damage;
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