#include "main.h"

PlayerAI::PlayerAI()
{
	characterLevel = 1;
	currentExperience = 0;
	maximumExperience = 1;
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
	if (entity != NULL)
	{
		inventoryComponent->removeFromStorage(entity);
		entity->setXPos(player->getXPos());
		entity->setYPos(player->getYPos());
		engine->addEntity(entity);
		engine->addToLog("You drop a " + entity->getName() + '.', TCOD_grey);
	}
}

void PlayerAI::equipItem(int c)
{
	Player* player = engine->getPlayer();
	InventoryComponent* inventoryComponent = player->getInventoryComponent();
	EquipmentComponent* equipmentComponent = player->getEquipmentComponent();
	Entity* entity = inventoryComponent->getItemAtLocation(c);
	if (entity != NULL)
	{
		ItemComponent* itemComponent = entity->getItemComponent();
		if (itemComponent != NULL)
		{
			EquipmentComponent::EQUIPMENTSLOT slot = itemComponent->getSlot();
			if (slot != EquipmentComponent::EQUIPMENTSLOT::none)
			{
				Entity* itemInSlot = equipmentComponent->getItemAtSlot(slot);
				if (itemInSlot != NULL)
				{
					itemInSlot->getItemComponent()->setEquipped(false);
					equipmentComponent->removeItemAtSlot(slot);
					modifyStatsOnItemDeEquip(itemInSlot->getItemComponent());
					engine->addToLog("You unequip " + itemInSlot->getName() + ".", TCOD_grey);
				}
				if (itemInSlot != entity)
				{
					equipmentComponent->setItemAtSlot(entity, slot);
					entity->getItemComponent()->setEquipped(true);
					modifyStatsOnItemEquip(itemComponent);
					engine->addToLog("You equip " + entity->getName() + ".", TCOD_grey);
				}
			}
		}
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
		engine->setRefresh(true);
		engine->setState(Engine::STATE::ENEMY_TURN);
		std::vector<Entity*> entities = engine->getEntities();
		int numOfEntities = (int)entities.size();
		for (int i = 0; i < numOfEntities; i++)
		{
			Entity* entity = entities[i];
			EnemyAI* enemy = entity->getEnemyAI();
			DestroyComponent* destroyComponent = entity->getDestroyComponent();
			ItemComponent* itemComponent = entity->getItemComponent();
			if (newX == entity->getXPos() && newY == entity->getYPos() && destroyComponent == NULL && itemComponent != NULL)
			{
				engine->addToLog("You see a " + entity->getName() + " here.", TCOD_grey);
			}
			else if (newX == entity->getXPos() && newY == entity->getYPos() && destroyComponent->isAlive())
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
	bool confirmed = false;
	std::vector<int> statSelections = { 0,0,0,0,0,0 };
	std::vector<TCODColor> selectionColorizer = { TCODColor::green, TCODColor::white, TCODColor::white,
													TCODColor::white, TCODColor::white, TCODColor::white };
	int selectionPointer = 0;
	currentExperience -= maximumExperience;
	maximumExperience = (int)round(maximumExperience * 1.5);
	characterLevel += 1;
	TCODConsole::root->clear();
	drawProgressionWindow(statSelections, selectionColorizer);
	TCODConsole::flush();
	while (!confirmed)
	{
		bool redraw = false;
		TCOD_key_t key;
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
		if (key.vk == TCODK_ESCAPE)
		{
			confirmed = true;
		}
		if (key.vk == TCODK_DOWN && selectionPointer < 5)
		{
			selectionColorizer[selectionPointer] = TCODColor::white;
			selectionPointer++;
			selectionColorizer[selectionPointer] = TCODColor::green;
			redraw = true;
		}
		if (key.vk == TCODK_UP && selectionPointer > 0)
		{
			selectionColorizer[selectionPointer] = TCODColor::white;
			selectionPointer--;
			selectionColorizer[selectionPointer] = TCODColor::green;
			redraw = true;
		}
		if (key.vk == TCODK_RIGHT && availableStatPoints > 0)
		{
			statSelections[selectionPointer]++;
			availableStatPoints--;
			redraw = true;
		}
		if (key.vk == TCODK_LEFT && statSelections[selectionPointer] > 0)
		{
			statSelections[selectionPointer]--;
			availableStatPoints++;
			redraw = true;
		}


		if (redraw)
		{
			TCODConsole::root->clear();
			drawProgressionWindow(statSelections, selectionColorizer);
			TCODConsole::flush();
		}
	}
	engine->addToLog("You have attained level " + std::to_string(characterLevel) + "!", TCOD_gold);
	/*TODO*/ 
	/*
	Stuff for character progression.
	Increase stats, increase attributes... etc.
	*/
}

void PlayerAI::modifyStatsOnItemEquip(ItemComponent* item)
{
	Player* player = engine->getPlayer();
	AttackComponent* attackComponent = player->getAttackComponent();
	DestroyComponent* destroyComponent = player->getDestroyComponent();

	attackComponent->adjustMinimumAttackPower(item->getMinimumDamage());
	attackComponent->adjustMaximumAttackPower(item->getMaximumDamage());

	destroyComponent->adjustArmor(item->getArmor());
	destroyComponent->adjustMaximumHealth(item->getHealth());
	destroyComponent->adjustMaximumMana(item->getMana());
	destroyComponent->adjustMaximumStamina(item->getStamina());
	destroyComponent->adjustDodge(item->getDodge());
	destroyComponent->adjustBlock(item->getBlock());
	destroyComponent->ajustParry(item->getParry());
}

void PlayerAI::modifyStatsOnItemDeEquip(ItemComponent* item)
{
	Player* player = engine->getPlayer();
	AttackComponent* attackComponent = player->getAttackComponent();
	DestroyComponent* destroyComponent = player->getDestroyComponent();

	attackComponent->adjustMinimumAttackPower(-item->getMinimumDamage());
	attackComponent->adjustMaximumAttackPower(-item->getMaximumDamage());

	destroyComponent->adjustArmor(-item->getArmor());
	destroyComponent->adjustMaximumHealth(-item->getHealth());
	destroyComponent->adjustMaximumMana(-item->getMana());
	destroyComponent->adjustMaximumStamina(-item->getStamina());
	destroyComponent->adjustDodge(-item->getDodge());
	destroyComponent->adjustBlock(-item->getBlock());
	destroyComponent->ajustParry(-item->getParry());
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