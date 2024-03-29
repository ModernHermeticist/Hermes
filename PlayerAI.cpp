#include "main.h"

PlayerAI::PlayerAI()
{
	characterLevel = 1;
	currentExperience = 0;
	maximumExperience = 10;
	target = NULL;
}

PlayerAI::~PlayerAI()
{
	if (target != NULL) delete target;
}

Engine::STATE PlayerAI::update()
{
	Engine::STATE newState = engine->getState();
	newState = parseKeyInput();
	return newState;
}

Engine::STATE PlayerAI::parseKeyInput()
{
	TCOD_key_t key = engine->getLastKey();
	Engine::STATE newState = engine->getState();
	switch (key.vk)
	{
		case TCODK_KP4:   newState = moveOrAttack(-1, 0, movementDirection::WEST); break;
		case TCODK_KP6:   newState = moveOrAttack(1, 0, movementDirection::EAST); break;
		case TCODK_KP8:   newState = moveOrAttack(0, -1, movementDirection::NORTH); break;
		case TCODK_KP2:   newState = moveOrAttack(0, 1, movementDirection::SOUTH); break;
		case TCODK_KP7:   newState = moveOrAttack(-1, -1, movementDirection::NORTHWEST); break;
		case TCODK_KP9:   newState = moveOrAttack(1, -1, movementDirection::NORTHEAST); break;
		case TCODK_KP1:   newState = moveOrAttack(-1, 1, movementDirection::SOUTHWEST); break;
		case TCODK_KP3:   newState = moveOrAttack(1, 1, movementDirection::SOUTHEAST); break;
		case TCODK_UP:
		{
			engine->incrementGeneralLogPointer();
			engine->setRefresh(true);
			break;
		}
		case TCODK_DOWN:
		{
			engine->decrementGeneralLogPointer();
			engine->setRefresh(true);
			break;
		}
		case TCODK_LEFT:
		{
			engine->incrementCombatLogPointer();
			engine->setRefresh(true);
			break;
		}
		case TCODK_RIGHT:
		{
			engine->decrementCombatLogPointer();
			engine->setRefresh(true);
			break;
		}
		default:break;
	}

	switch (key.c)
	{
		case 'c':
		{
			newState = Engine::STATE::SHOW_CHARACTER_SCREEN;
			break;
		}
		case 'g':
		{
			newState = Engine::STATE::PICK_UP_ITEM;
			break;
		}
		case 'i':
		{
			newState = Engine::STATE::SHOW_INVENTORY_SCREEN;
			break;
		}
		case 't':
		{
			engine->getPlayer()->getPlayerAI()->selectTarget();
			engine->setRefresh(true);
			break;
		}

		case 'a':   newState = moveOrAttack(-1, 0, movementDirection::WEST); break;
		case 'd':   newState = moveOrAttack(1, 0, movementDirection::EAST); break;
		case 'w':   newState = moveOrAttack(0, -1, movementDirection::NORTH); break;
		case 's':   newState = moveOrAttack(0, 1, movementDirection::SOUTH); break;


		default: break;
	}
	return newState;
}

Engine::STATE PlayerAI::pickUpItem()
{
	std::vector<Entity*> entities = engine->getEntities();
	Player* player = engine->getPlayer();
	InventoryComponent* inventoryComponent = player->getInventoryComponent();
	int xPos = player->getXPos();
	int yPos = player->getYPos();
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* entity = *it;
		ItemComponent* itemComponent = entity->getItemComponent();
		if (itemComponent != NULL && entity->getXPos() == xPos && entity->getYPos() == yPos)
		{
			if (inventoryComponent->getCurrentStorageSize() == inventoryComponent->getStorageCapacity())
			{
				engine->addToGeneralLog("Inventory is full.", TCOD_grey);
				return engine->getState();
			}
			else
			{
				inventoryComponent->addToStorage(entity);
				engine->removeEntity(entity);
				engine->addToGeneralLog("You pick up a " + entity->getName(), TCOD_grey);
				return Engine::STATE::ENEMY_TURN;
			}
		}
	}
	engine->addToGeneralLog("There is nothing here to pick up.", TCOD_grey);
	return engine->getState();
}

Engine::STATE PlayerAI::dropItem(int c)
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
		engine->addToGeneralLog("You drop a " + entity->getName() + '.', TCOD_grey);
		return Engine::STATE::ENEMY_TURN;
	}
	return engine->getState();
}

Engine::STATE PlayerAI::equipItem(int c)
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
					engine->addToGeneralLog("You unequip " + itemInSlot->getName() + ".", TCOD_grey);
				}
				if (itemInSlot != entity)
				{
					equipmentComponent->setItemAtSlot(entity, slot);
					entity->getItemComponent()->setEquipped(true);
					modifyStatsOnItemEquip(itemComponent);
					engine->addToGeneralLog("You equip " + entity->getName() + ".", TCOD_grey);
				}
			}
		}
	}
	return Engine::STATE::ENEMY_TURN;
}

Engine::STATE PlayerAI::useItem(int c)
{
	Player* player = engine->getPlayer();
	InventoryComponent* inventoryComponent = player->getInventoryComponent();
	Entity* entity = inventoryComponent->getItemAtLocation(c);
	if (entity == NULL)
	{
		return engine->getState();
	}
	ItemComponent* itemComponent = entity->getItemComponent();
	ConsumableComponent* consumableComponent = itemComponent->getConsumableComponent();
	if (consumableComponent == NULL) return engine->getState();

	EffectComponent* effectComponent = consumableComponent->getEffectComponent();
	if (effectComponent == NULL) return engine->getState();

	EffectComponent::Effect_Type effectType = effectComponent->getEffectType();
	if (effectType == EffectComponent::Effect_Type::HEAL)
	{
		engine->addToGeneralLog("You use the " + entity->getName(), TCODColor::grey);
		heal(effectComponent->getEffectValue());
		inventoryComponent->removeFromStorage(entity);
		engine->removeEntity(entity);
	}
	return Engine::STATE::ENEMY_TURN;
}

Engine::STATE PlayerAI::inspectItem(int c)
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
			bool confirmed = false;
			while (!confirmed)
			{
				TCODConsole::root->clear();
				drawInspectionWindow(entity);
				TCODConsole::flush();
				TCOD_key_t key;
				TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
				if (key.vk == TCODK_ESCAPE)
				{
					confirmed = true;
					key.vk = (TCOD_keycode_t)0;
				}
			}
			return Engine::STATE::SHOW_INVENTORY_SCREEN;
		}
	}
	return engine->getState();
}


Engine::STATE PlayerAI::moveOrAttack(int dX, int dY, movementDirection dir)
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
		int numOfEntities = (int)entities.size();
		for (int i = 0; i < numOfEntities; i++)
		{
			Entity* entity = entities[i];
			EnemyAI* enemy = entity->getEnemyAI();
			DestroyComponent* destroyComponent = entity->getDestroyComponent();
			ItemComponent* itemComponent = entity->getItemComponent();
			if (newX == entity->getXPos() && newY == entity->getYPos() && destroyComponent == NULL && itemComponent != NULL)
			{
				engine->addToGeneralLog("You see a " + entity->getName() + " here.", TCOD_grey);
			}
			else if (newX == entity->getXPos() && newY == entity->getYPos() && destroyComponent->isAlive())
			{
				AttackComponent* attackComponent = player->getAttackComponent();
				int damage = attackComponent->getDamage();
				std::vector<int> retVal = enemy->takeDamage(entity, damage);
				damage = retVal[0];
				engine->addToCombatLog("You hit a " + entity->getName() + " for " + std::to_string(damage) + " damage!", TCOD_red);
				if (retVal[1] == -1)
				{
					engine->addToGeneralLog(entity->getName() + " dies!", TCOD_darker_red);
					return gainExperience(destroyComponent->getExperienceValue());
				}
				engine->setComputeFov(true);
				return Engine::STATE::ENEMY_TURN;
			}
		}
		engine->setComputeFov(true);
		player->updatePosition(dX, dY);
		return Engine::STATE::ENEMY_TURN;
	}
	else
	{
		engine->addToGeneralLog("You cannot move there.", TCOD_grey);
		return Engine::STATE::PLAYER_TURN;
	}
}

Engine::STATE PlayerAI::gainExperience(int val)
{
	currentExperience += val; 
	engine->addToGeneralLog("You gain " + std::to_string(val) + " experience!", TCOD_gold);
	if (currentExperience >= maximumExperience)
	{
		return Engine::STATE::PROGRESS_CHARACTER;
	}
	return Engine::STATE::ENEMY_TURN;
}

int PlayerAI::getCharacterLevel() { return characterLevel; }
int PlayerAI::getCurrentExperience() { return currentExperience; }
int PlayerAI::getMaximumExperience() { return maximumExperience; }

Engine::STATE PlayerAI::progressCharacter()
{
	bool confirmed = false;
	std::vector<int> statSelections = { 0,0,0,0,0,0 };
	std::vector<TCODColor> selectionColorizer = { TCODColor::green, TCODColor::white, TCODColor::white,
													TCODColor::white, TCODColor::white, TCODColor::white, TCODColor::white };
	int selectionPointer = 0;
	currentExperience -= maximumExperience;
	maximumExperience = (int)round(maximumExperience * 1.5);
	availableStatPoints += 5;
	characterLevel += 1;
	TCODConsole::root->clear();
	drawProgressionWindow(statSelections, selectionColorizer, availableStatPoints);
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
		if (key.vk == TCODK_DOWN && selectionPointer < 6)
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
		if (key.vk == TCODK_ENTER && availableStatPoints == 0)
		{
			applyStatPoints(statSelections);
			recalculateStats();
			confirmed = true;
		}


		if (redraw)
		{
			TCODConsole::root->clear();
			drawProgressionWindow(statSelections, selectionColorizer, availableStatPoints);
			TCODConsole::flush();
		}
	}
	engine->addToGeneralLog("You have attained level " + std::to_string(characterLevel) + "!", TCOD_gold);
	return Engine::STATE::ENEMY_TURN;
}

void PlayerAI::applyStatPoints(std::vector<int> statSelections)
{
	Player* player = engine->getPlayer();
	DestroyComponent* destroyComponent = player->getDestroyComponent();

	destroyComponent->adjustStrength(statSelections[0]);
	destroyComponent->adjustAgility(statSelections[1]);
	destroyComponent->adjustEndurance(statSelections[2]);
	destroyComponent->adjustLuck(statSelections[3]);
	destroyComponent->adjustIntelligence(statSelections[4]);
	destroyComponent->adjustWisdom(statSelections[5]);
}

void PlayerAI::recalculateStats()
{
	Player* player = engine->getPlayer();
	AttackComponent* attackComponent = player->getAttackComponent();
	DestroyComponent* destroyComponent = player->getDestroyComponent();

	EquipmentComponent* equipmentComponent = player->getEquipmentComponent();
	std::vector<Entity*> allItemSlots = equipmentComponent->getAllItemSlots();
	for (std::vector<Entity*>::iterator it = allItemSlots.begin(); it != allItemSlots.end(); it++)
	{
		Entity* item = *it;
		if (item != NULL)
		{
			modifyStatsOnItemDeEquip(item->getItemComponent());
		}
	}

	destroyComponent->applyBaseStatsToFinal();

	attackComponent->setMinimumAttackPower(attackComponent->standardMinimumAttackPowerAdjustment());
	attackComponent->setMaximumAttackPower(attackComponent->standardMaximumAttackPowerAdjustment());
	destroyComponent->setBlock(destroyComponent->standardBlockAdjustment());
	destroyComponent->setDodge(destroyComponent->standardDodgeAdjustment());
	destroyComponent->setParry(destroyComponent->standardParryAdjustment());
	destroyComponent->setMaximumHealth(destroyComponent->standardHealthAdjustment());
	destroyComponent->setMaximumStamina(destroyComponent->standardStaminaAdjustment());
	destroyComponent->setMaximumMana(destroyComponent->standardManaAdjustment());

	destroyComponent->applyOtherBaseStatsToFinal();
	attackComponent->applyBaseStatsToFinal();

	for (std::vector<Entity*>::iterator it = allItemSlots.begin(); it != allItemSlots.end(); it++)
	{
		Entity* item = *it;
		if (item != NULL)
		{
			modifyStatsOnItemEquip(item->getItemComponent());
		}
	}
}

void PlayerAI::modifyStatsOnItemEquip(ItemComponent* item)
{
	Player* player = engine->getPlayer();
	AttackComponent* attackComponent = player->getAttackComponent();
	DestroyComponent* destroyComponent = player->getDestroyComponent();

	attackComponent->adjustFinalMinimumAttackPowerByItem(item->getMinimumDamage());
	attackComponent->adjustFinalMaximumAttackPowerByItem(item->getMaximumDamage());

	destroyComponent->adjustFinalArmorByItem(item->getArmor());
	destroyComponent->adjustFinalMaximumHealthByItem(item->getHealth());
	destroyComponent->adjustFinalMaximumManaByItem(item->getMana());
	destroyComponent->adjustFinalMaximumStaminaByItem(item->getStamina());
	destroyComponent->adjustFinalDodgeByItem(item->getDodge());
	destroyComponent->adjustFinalBlockByItem(item->getBlock());
	destroyComponent->adjustFinalParryByItem(item->getParry());
}

void PlayerAI::modifyStatsOnItemDeEquip(ItemComponent* item)
{
	Player* player = engine->getPlayer();
	AttackComponent* attackComponent = player->getAttackComponent();
	DestroyComponent* destroyComponent = player->getDestroyComponent();

	attackComponent->adjustFinalMinimumAttackPowerByItem(-item->getMinimumDamage());
	attackComponent->adjustFinalMaximumAttackPowerByItem(-item->getMaximumDamage());

	destroyComponent->adjustFinalArmorByItem(-item->getArmor());
	destroyComponent->adjustFinalMaximumHealthByItem(-item->getHealth());
	destroyComponent->adjustFinalMaximumManaByItem(-item->getMana());
	destroyComponent->adjustFinalMaximumStaminaByItem(-item->getStamina());
	destroyComponent->adjustFinalDodgeByItem(-item->getDodge());
	destroyComponent->adjustFinalBlockByItem(-item->getBlock());
	destroyComponent->adjustFinalParryByItem(-item->getParry());
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
	engine->addToCombatLog("You heal " + std::to_string(val) + " hitpoints.", TCODColor::green);
}

void PlayerAI::selectTarget()
{
	Player* player = engine->getPlayer();
	int pointerX = player->getXPos();
	int pointerY = player->getYPos() - 1;
	int oldX = pointerX;
	int oldY = pointerY;
	int cardinalDirection = 0;
	int oldCardinalDirection = cardinalDirection;

	bool confirmed = false;

	int range = 3;
	while (!confirmed)
	{
		TCODConsole::root->clear();
		//highlightConeTiles(cardinalDirection, oldCardinalDirection, range, 0, engine->getMap(), engine->getPlayer(), engine->getEntities());
		//highlightLineTiles(cardinalDirection, oldCardinalDirection, 3, engine->getMap(), engine->getPlayer(), engine->getEntities());
		//highlightAOETiles(pointerX, pointerY, oldX, oldY, 2, engine->getMap(), engine->getPlayer(), engine->getEntities());
		highlightTile(pointerX, pointerY, oldX, oldY, engine->getMap(), engine->getPlayer(), engine->getEntities());
		drawUI();
		TCODConsole::flush();
		TCOD_key_t key;
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
		oldX = pointerX;
		oldY = pointerY;
		oldCardinalDirection = cardinalDirection;
		if (key.vk == TCODK_LEFT)
		{
			if (cardinalDirection == 0) cardinalDirection = 7;
			else cardinalDirection--;
		}
		if (key.vk == TCODK_RIGHT)
		{
			if (cardinalDirection == 7) cardinalDirection = 0;
			else cardinalDirection++;
		}
		if (key.vk == TCODK_ESCAPE || key.vk == TCODK_ENTER) confirmed = true;
		if (key.vk == TCODK_KP8) pointerY--;
		else if (key.vk == TCODK_KP2) pointerY++;
		else if (key.vk == TCODK_KP4) pointerX--;
		else if (key.vk == TCODK_KP6) pointerX++;
		else if (key.vk == TCODK_KP1)
		{
			pointerX--;
			pointerY++;
		}
		else if (key.vk == TCODK_KP3)
		{
			pointerX++;
			pointerY++;
		}
		else if (key.vk == TCODK_KP7)
		{
			pointerX--;
			pointerY--;
		}
		else if (key.vk == TCODK_KP9)
		{
			pointerX++;
			pointerY--;
		}
		if (!engine->getMap()->isInFov(pointerX,pointerY))
		{
			pointerX = oldX;
			pointerY = oldY;
		}
	}
	resetConeHighlight(cardinalDirection, range, 0, engine->getMap(), engine->getPlayer(), engine->getEntities());
	//resetLineHighlight(cardinalDirection, 3, engine->getMap(), engine->getPlayer(), engine->getEntities());
	//resetAOEHighlight(pointerX, pointerY, 2, engine->getMap(), engine->getPlayer(), engine->getEntities());
	//resetHighlight(pointerX, pointerY, engine->getMap(), engine->getPlayer(), engine->getEntities());
}

Entity* PlayerAI::getTarget() { return target; }
void PlayerAI::setTarget(Entity* newTarget) { target = newTarget; }