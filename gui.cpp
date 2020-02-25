#include "main.h"

void drawMainBorder()
{
	int borderWidth = MAIN_WINDOW_WIDTH;
	int borderHeight = MAIN_WINDOW_HEIGHT;
	TCODColor borderColor = TCOD_darker_green;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	con->putCharEx(0, 0, TOP_FORK_WALL, borderColor, TCOD_black);
	con->putCharEx(0, borderHeight-1, CROSS_WALL, borderColor, TCOD_black);
	con->putCharEx(borderWidth-1, 0, TOP_RIGHT_CORNER_WALL, borderColor, TCOD_black);
	con->putCharEx(borderWidth - 1, borderHeight-1, RIGHT_FORK_WALL, borderColor, TCOD_black);
	for (int i = 1; i < borderWidth-1; i++)
	{
		con->putCharEx(i, 0, HORIZONTAL_WALL, borderColor, TCOD_black);
		con->putCharEx(i, borderHeight-1, HORIZONTAL_WALL, borderColor, TCOD_black);
	}
	for (int i = 1; i < borderHeight-1; i++)
	{
		con->putCharEx(0, i, VERTICAL_WALL, borderColor, TCOD_black);
		con->putCharEx(borderWidth-1, i, VERTICAL_WALL, borderColor, TCOD_black);
	}

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, CELL_COLUMNS - borderWidth, 0);
	delete con;
}

void drawMainWindow(Map* map, Player* player, std::vector<Entity*> entities)
{
	int borderWidth = MAIN_WINDOW_WIDTH - 2;
	int borderHeight = MAIN_WINDOW_HEIGHT - 2;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);

	int width = engine->getWorldWidth();
	int height = engine->getWorldHeight();
	Tile** tiles = map->getWorld();
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Tile* tile = &tiles[x][y];
			if (map->isInFov(x, y))
			{
				con->putCharEx(tile->getXPos(), tile->getYPos(), tile->getSprite(), tile->getVisibleForeground(), tile->getVisibleBackground());
			}
			else if (tile->getExplored())
			{
				con->putCharEx(tile->getXPos(), tile->getYPos(), tile->getSprite(), tile->getExploredForeground(), tile->getExploredBackground());
			}
		}
	}
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		Entity* entity = *it;
		if (map->isInFov(entity->getXPos(), entity->getYPos()))
		{
			con->putCharEx(entity->getXPos(), entity->getYPos(), entity->getSprite(), entity->getSpriteForeground(), entity->getSpriteBackground());
		}
	}
	con->putCharEx(player->getXPos(), player->getYPos(), player->getSprite(), player->getSpriteForeground(), player->getSpriteBackground());
	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, CELL_COLUMNS - borderWidth-1, 1);
	delete con;
}

void drawUtilityWindow()
{
	int borderWidth = UTILITY_WINDOW_WIDTH;
	int borderHeight = UTILITY_WINDOW_HEIGHT;
	TCODColor borderColor = TCOD_darker_green;
	Player* player = engine->getPlayer();
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);

	con->putCharEx(0, 0, TOP_LEFT_CORNER_WALL, borderColor, TCOD_black);
	con->putCharEx(0, borderHeight - 1, BOTTOM_LEFT_CORNER_WALL, borderColor, TCOD_black);
	con->putCharEx(borderWidth - 1, 0, TOP_RIGHT_CORNER_WALL, borderColor, TCOD_black);
	con->putCharEx(borderWidth - 1, borderHeight - 1, BOTTOM_RIGHT_CORNER_WALL, borderColor, TCOD_black);

	for (int i = 1; i < borderWidth-1; i++)
	{
		con->putCharEx(i, 0, HORIZONTAL_WALL, borderColor, TCOD_black);
		con->putCharEx(i, borderHeight - 1, HORIZONTAL_WALL, borderColor, TCOD_black);
	}
	for (int i = 1; i < borderHeight-1; i++)
	{
		con->putCharEx(0, i, VERTICAL_WALL, borderColor, TCOD_black);
		con->putCharEx(borderWidth - 1, i, VERTICAL_WALL, borderColor, TCOD_black);
	}
	DestroyComponent* destroyComponent = player->getDestroyComponent();
	PlayerAI* playerAI = player->getPlayerAI();
	destroyComponent->getCurrentStamina();
	std::string s = "" + player->getName() + ", Level " + std::to_string(playerAI->getCharacterLevel());
	con->printf(1, 1, s.c_str());
	s = "%cHealth: " + std::to_string(destroyComponent->getCurrentHealth())
		+ '/' + std::to_string(destroyComponent->getMaximumHealth()) + "%c";
	con->setColorControl(TCOD_COLCTRL_1, TCODColor::darkRed, TCODColor::black);
	con->printf(1, 2, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	s = "%cStamina: " + std::to_string(destroyComponent->getCurrentStamina())
		+ '/' + std::to_string(destroyComponent->getMaximumStamina()) + "%c";
	con->setColorControl(TCOD_COLCTRL_1, TCODColor::darkGreen, TCODColor::black);
	con->printf(1, 3, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	s = "%cMana: " + std::to_string(destroyComponent->getCurrentMana())
		+ '/' + std::to_string(destroyComponent->getMaximumMana()) + "%c";
	con->setColorControl(TCOD_COLCTRL_1, TCODColor::azure, TCODColor::black);
	con->printf(1, 4, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	s = "%cExperience: " + std::to_string(playerAI->getCurrentExperience())
		+ '/' + std::to_string(playerAI->getMaximumExperience()) + "%c";
	con->setColorControl(TCOD_COLCTRL_1, TCODColor::gold, TCODColor::black);
	con->printf(1, 5, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, 0, 0);
	delete con;
}

void drawTargetWindow()
{
	int borderWidth = UTILITY_WINDOW_WIDTH;
	int borderHeight = LOG_WINDOW_HEIGHT;
	TCODColor borderColor = TCOD_darker_green;
	Player* player = engine->getPlayer();
	PlayerAI* playerAI = player->getPlayerAI();
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	std::string s = "Target:";
	Entity* target = playerAI->getTarget();

	drawBorder(con, borderHeight, borderWidth, borderColor);
	con->putCharEx(0, 0, LEFT_FORK_WALL, borderColor, TCODColor::black);
	con->printf(1, 1, s.c_str());
	if (target != NULL)
	{
		s = playerAI->getTarget()->getName();
	}
	else
	{
		s = "";
	}
	wrapTextWithinBounds(con, s, 1, 2, borderWidth - 2, borderHeight - 2);

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, 0, CELL_ROWS - borderHeight);
	delete con;
}

void drawLogWindow()
{
	int borderWidth = LOG_WINDOW_WIDTH;
	int borderHeight = LOG_WINDOW_HEIGHT;
	TCODColor borderColor = TCOD_darker_green;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);

	con->putCharEx(0, 0, TOP_LEFT_CORNER_WALL, borderColor, TCOD_black);
	con->putCharEx(0, borderHeight - 1, BOTTOM_FORK_WALL, borderColor, TCOD_black);
	con->putCharEx(borderWidth - 1, 0, RIGHT_FORK_WALL, borderColor, TCOD_black);
	con->putCharEx(borderWidth - 1, borderHeight - 1, BOTTOM_RIGHT_CORNER_WALL, borderColor, TCOD_black);

	for (int i = 1; i < borderWidth - 1; i++)
	{
		con->putCharEx(i, 0, HORIZONTAL_WALL, borderColor, TCOD_black);
		con->putCharEx(i, borderHeight - 1, HORIZONTAL_WALL, borderColor, TCOD_black);
	}
	for (int i = 1; i < borderHeight - 1; i++)
	{
		con->putCharEx(0, i, VERTICAL_WALL, borderColor, TCOD_black);
		con->putCharEx(borderWidth - 1, i, VERTICAL_WALL, borderColor, TCOD_black);
	}

	con->putCharEx(0, 1, 16 * 2 - 2, borderColor, TCOD_black);
	con->putCharEx(0, borderHeight - 2, 16 * 2 - 1, borderColor, TCOD_black);

	std::vector<LogEntry> log = engine->getLog();
	if (log.size() < 7)
	{
		for (int i = 0; i < log.size(); i++)
		{
			LogEntry entry = log[i];
			std::string s = entry.getEntry();
			for (int k = 0; k < s.size(); k++)
			{
				con->putCharEx(k + 1, i + 1, s[k], entry.getEntryColor(), TCOD_black);
			}
		}
	}
	else
	{
		int logPointer = engine->getLogPointer();
		int pos = 0;
		for (int i = log.size() - 7 - logPointer; i < log.size() - logPointer; i++)
		{
			LogEntry entry = log[i];
			std::string s = entry.getEntry();
			for (int k = 0; k < s.size(); k++)
			{
				con->putCharEx(k + 1, pos + 1, s[k], entry.getEntryColor(), TCOD_black);
			}
			pos++;
		}
	}

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, CELL_COLUMNS - borderWidth, MAIN_WINDOW_HEIGHT-1);
	delete con;
}

void drawCharacterWindow()
{
	Player* player = engine->getPlayer();
	AttackComponent* attackComponent = player->getAttackComponent();
	DestroyComponent* destroyComponent = player->getDestroyComponent();
	EquipmentComponent* equipmentComponent = player->getEquipmentComponent();

	int borderWidth = CELL_COLUMNS;
	int borderHeight = CELL_ROWS;
	TCODColor borderColor = TCOD_darker_green;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	drawBorder(con, borderHeight, borderWidth, borderColor);
	std::string s = "Character Sheet";
	con->printf(CELL_COLUMNS / 2 - (int)s.size() / 2, 1, s.c_str());
	s = "Name:         " + player->getName();
	con->printf(1, 2, s.c_str());
	s = "Health:       " + std::to_string(destroyComponent->getCurrentHealth()) + '/' +
		std::to_string(destroyComponent->getMaximumHealth());
	con->printf(1, 3, s.c_str());
	s = "Stamina:      " + std::to_string(destroyComponent->getCurrentStamina()) + '/' +
		std::to_string(destroyComponent->getMaximumStamina());
	con->printf(1, 4, s.c_str());
	s = "Mana:         " + std::to_string(destroyComponent->getCurrentMana()) + '/' +
		std::to_string(destroyComponent->getMaximumMana());
	con->printf(1, 5, s.c_str());

	s = "Damage:       " + std::to_string(attackComponent->getMinimumAttackPower()) + '-' +
		std::to_string(attackComponent->getMaximumAttackPower());
	con->printf(1, 6, s.c_str());
	s = "Armor:        " + std::to_string(destroyComponent->getArmor());
	con->printf(1, 7, s.c_str());
	s = "Block:        " + std::to_string(destroyComponent->getBlock());
	con->printf(1, 8, s.c_str());
	s = "Dodge:        " + std::to_string(destroyComponent->getDodge());
	con->printf(1, 9, s.c_str());
	s = "Parry:        " + std::to_string(destroyComponent->getParry());
	con->printf(1, 10, s.c_str());

	s = "Strength:     " + std::to_string(destroyComponent->getStrength());
	con->printf(1, 11, s.c_str());
	s = "Agility:      " + std::to_string(destroyComponent->getAgility());
	con->printf(1, 12, s.c_str());
	s = "Endurance:    " + std::to_string(destroyComponent->getEndurance());
	con->printf(1, 13, s.c_str());
	s = "Luck:         " + std::to_string(destroyComponent->getLuck());
	con->printf(1, 14, s.c_str());
	s = "Intelligence: " + std::to_string(destroyComponent->getIntelligence());
	con->printf(1, 15, s.c_str());
	s = "Wisdom:       " + std::to_string(destroyComponent->getWisdom());
	con->printf(1, 16, s.c_str());

	Entity* itemInSlot = equipmentComponent->getRightHand();
	int equipmentPosition = 25;
	if (itemInSlot != NULL)
		s = "Right Hand:    " + itemInSlot->getName();
	else s = "Right Hand:    None";
	con->printf(equipmentPosition, 2, s.c_str());

	itemInSlot = equipmentComponent->getLeftHand();
	if (itemInSlot != NULL)
		s = "Left Hand:     " + itemInSlot->getName();
	else s = "Left Hand:     None";
	con->printf(equipmentPosition, 3, s.c_str());

	itemInSlot = equipmentComponent->getHead();
	if (itemInSlot != NULL)
		s = "Head:          " + itemInSlot->getName();
	else s = "Head:          None";
	con->printf(equipmentPosition, 4, s.c_str());

	itemInSlot = equipmentComponent->getShoulders();
	if (itemInSlot != NULL)
		s = "Shoulders:     " + itemInSlot->getName();
	else s = "Shoulders:     None";
	con->printf(equipmentPosition, 5, s.c_str());

	itemInSlot = equipmentComponent->getNeck();
	if (itemInSlot != NULL)
		s = "Neck:          " + itemInSlot->getName();
	else s = "Neck:          None";
	con->printf(equipmentPosition, 6, s.c_str());

	itemInSlot = equipmentComponent->getChest();
	if (itemInSlot != NULL)
		s = "Chest:         " + itemInSlot->getName();
	else s = "Chest:         None";
	con->printf(equipmentPosition, 7, s.c_str());

	itemInSlot = equipmentComponent->getWaist();
	if (itemInSlot != NULL)
		s = "Waist:         " + itemInSlot->getName();
	else s = "Waist:         None";
	con->printf(equipmentPosition, 8, s.c_str());

	itemInSlot = equipmentComponent->getHands();
	if (itemInSlot != NULL)
		s = "Hands:         " + itemInSlot->getName();
	else s = "Hands:         None";
	con->printf(equipmentPosition, 9, s.c_str());

	itemInSlot = equipmentComponent->getLegs();
	if (itemInSlot != NULL)
		s = "Legs:          " + itemInSlot->getName();
	else s = "Legs:          None";
	con->printf(equipmentPosition, 10, s.c_str());

	itemInSlot = equipmentComponent->getFeet();
	if (itemInSlot != NULL)
		s = "Feet:          " + itemInSlot->getName();
	else s = "Feet:          None";
	con->printf(equipmentPosition, 11, s.c_str());

	itemInSlot = equipmentComponent->getLeftRing();
	if (itemInSlot != NULL)
		s = "Left Ring:     " + itemInSlot->getName();
	else s = "Left Ring:     None";
	con->printf(equipmentPosition, 12, s.c_str());

	itemInSlot = equipmentComponent->getRightRing();
	if (itemInSlot != NULL)
		s = "Right Ring:    " + itemInSlot->getName();
	else s = "Right Ring:    None";
	con->printf(equipmentPosition, 13, s.c_str());

	itemInSlot = equipmentComponent->getLeftEarring();
	if (itemInSlot != NULL)
		s = "Left Earring:  " + itemInSlot->getName();
	else s = "Left Earring:  None";
	con->printf(equipmentPosition, 14, s.c_str());

	itemInSlot = equipmentComponent->getRightEarring();
	if (itemInSlot != NULL)
		s = "Right Earring: " + itemInSlot->getName();
	else s = "Right Earring: None";
	con->printf(equipmentPosition, 15, s.c_str());

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, 0, 0);
	delete con;
}

void drawInventoryWindow()
{
	Player* player = engine->getPlayer();
	InventoryComponent* inventoryComponent = player->getInventoryComponent();
	std::vector<Entity*> storage = inventoryComponent->getStorage();
	int size = (int)storage.size();

	int borderWidth = CELL_COLUMNS;
	int borderHeight = CELL_ROWS;
	TCODColor borderColor = TCOD_darker_green;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	drawBorder(con, borderHeight, borderWidth, borderColor);
	std::string s = "Inventory";
	std::stringstream ss;
	con->printf(1 + ((CELL_COLUMNS - 1) / 2 - (int)s.size() / 2), 1, s.c_str());
	con->printf(1, CELL_ROWS - 2, "    Use: (letter)    Equip: (shift+letter)    Drop: (ctrl+letter)    Inspect: (alt+letter)");
	if (storage.size() > 0)
	{
		char label = 97;
		for (int i = 0; i < size; i++)
		{
			label += i;
			if (storage[i]->getItemComponent()->isEquipped())
				ss << label << ") " << storage[i]->getName() << " (e)";
			else ss << label << ") " << storage[i]->getName();
			con->printf(1, i + 2, ss.str().c_str());
			ss.str(std::string());
		}
	}

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, 0, 0);
	delete con;
}

void drawBorder(TCODConsole* con, int borderHeight, int borderWidth, TCODColor borderColor)
{
	con->putCharEx(0, 0, TOP_LEFT_CORNER_WALL, borderColor, TCOD_black);
	con->putCharEx(0, borderHeight - 1, BOTTOM_LEFT_CORNER_WALL, borderColor, TCOD_black);
	con->putCharEx(borderWidth - 1, 0, TOP_RIGHT_CORNER_WALL, borderColor, TCOD_black);
	con->putCharEx(borderWidth - 1, borderHeight - 1, BOTTOM_RIGHT_CORNER_WALL, borderColor, TCOD_black);

	for (int i = 1; i < borderWidth - 1; i++)
	{
		con->putCharEx(i, 0, HORIZONTAL_WALL, borderColor, TCOD_black);
		con->putCharEx(i, borderHeight - 1, HORIZONTAL_WALL, borderColor, TCOD_black);
	}
	for (int i = 1; i < borderHeight - 1; i++)
	{
		con->putCharEx(0, i, VERTICAL_WALL, borderColor, TCOD_black);
		con->putCharEx(borderWidth - 1, i, VERTICAL_WALL, borderColor, TCOD_black);
	}
}

void drawProgressionWindow(std::vector<int> selections, std::vector<TCODColor> selectionColorizer)
{
	Player* player = engine->getPlayer();
	AttackComponent* attackComponent = player->getAttackComponent();
	DestroyComponent* destroyComponent = player->getDestroyComponent();

	int borderWidth = CELL_COLUMNS;
	int borderHeight = CELL_ROWS;
	TCODColor borderColor = TCOD_darker_green;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	drawBorder(con, borderHeight, borderWidth, borderColor);
	std::string s = "Progression";
	con->printf(CELL_COLUMNS / 2 - (int)s.size() / 2, 1, s.c_str());
	con->setColorControl(TCOD_COLCTRL_1, TCODColor::grey, TCODColor::black);
	if (selections[2] > 0)
	{
		con->setColorControl(TCOD_COLCTRL_1, TCODColor::gold, TCODColor::black);
		s = "%cHealth:       " + std::to_string(destroyComponent->getCurrentHealth()) + '/' +
			std::to_string(destroyComponent->getMaximumHealth()) + " --> " +
			std::to_string(destroyComponent->getCurrentHealth()) + '/' +
			std::to_string(destroyComponent->standardHealthAdjustmentPreview(selections[2])) + "%c";
	}
	else
	{
		s = "%cHealth:       " + std::to_string(destroyComponent->getCurrentHealth()) + '/' +
			std::to_string(destroyComponent->getMaximumHealth()) + "%c";
	}
	con->printf(1, 3, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, TCODColor::grey, TCODColor::black);
	if (selections[2] > 0)
	{
		con->setColorControl(TCOD_COLCTRL_1, TCODColor::gold, TCODColor::black);
		s = "%cStamina:      " + std::to_string(destroyComponent->getCurrentStamina()) + '/' +
			std::to_string(destroyComponent->getMaximumStamina()) + " --> " +
			std::to_string(destroyComponent->getCurrentStamina()) + '/' +
			std::to_string(destroyComponent->standardStaminaAdjustmentPreview(selections[2])) + "%c";
	}
	else
	{
		s = "%cStamina:      " + std::to_string(destroyComponent->getCurrentStamina()) + '/' +
			std::to_string(destroyComponent->getMaximumStamina()) + "%c";
	}
	con->printf(1, 4, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, TCODColor::grey, TCODColor::black);
	if (selections[4] > 0)
	{
		con->setColorControl(TCOD_COLCTRL_1, TCODColor::gold, TCODColor::black);
		s = "%cMana:         " + std::to_string(destroyComponent->getCurrentMana()) + '/' +
			std::to_string(destroyComponent->getMaximumMana()) + " --> " +
			std::to_string(destroyComponent->getCurrentMana()) + '/' +
			std::to_string(destroyComponent->standardManaAdjustmentPreview(selections[4])) + "%c";
	}
	else
	{
		s = "%cMana:         " + std::to_string(destroyComponent->getCurrentMana()) + '/' +
			std::to_string(destroyComponent->getMaximumMana()) + "%c";
	}
	con->printf(1, 5, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, TCODColor::grey, TCODColor::black);
	if (selections[0] > 0)
	{
		con->setColorControl(TCOD_COLCTRL_1, TCODColor::gold, TCODColor::black);
		s = "%cDamage:       " + std::to_string(attackComponent->getMinimumAttackPower()) + '-' +
			std::to_string(attackComponent->getMaximumAttackPower()) + " --> " +
			std::to_string(attackComponent->standardMinimumAttackPowerAdjustmentPreview(selections[0])) + '-' +
			std::to_string(attackComponent->standardMaximumAttackPowerAdjustmentPreview(selections[0])) + "%c";
	}
	else
	{
		s = "%cDamage:       " + std::to_string(attackComponent->getMinimumAttackPower()) + '-' +
			std::to_string(attackComponent->getMaximumAttackPower()) + "%c";
	}
	con->printf(1, 6, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, TCODColor::grey, TCODColor::black);
	s = "%cArmor:        " + std::to_string(destroyComponent->getArmor()) + "%c";
	con->printf(1, 7, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	if (selections[1] > 0 || selections[3] > 0)
	{
		con->setColorControl(TCOD_COLCTRL_1, TCODColor::gold, TCODColor::black);
		s = "%cDodge:        " + std::to_string(destroyComponent->getDodge()) + " --> " +
			std::to_string(destroyComponent->standardDodgeAdjustmentPreview(selections[1], selections[3])) + "%c";
		con->printf(1, 9, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
		s = "%cParry:        " + std::to_string(destroyComponent->getParry()) + " --> " +
			std::to_string(destroyComponent->standardParryAdjustmentPreview(selections[1], selections[3])) + "%c";
		con->printf(1, 10, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	}
	else
	{
		s = "%cDodge:        " + std::to_string(destroyComponent->getDodge()) + "%c";
		con->printf(1, 9, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
		s = "%cParry:        " + std::to_string(destroyComponent->getParry()) + "%c";
		con->printf(1, 10, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	}

	con->setColorControl(TCOD_COLCTRL_1, TCODColor::grey, TCODColor::black);
	if (selections[0] > 0 || selections[3] > 0)
	{
		con->setColorControl(TCOD_COLCTRL_1, TCODColor::gold, TCODColor::black);
		s = "%cBlock:        " + std::to_string(destroyComponent->getBlock()) + " --> " +
			std::to_string(destroyComponent->standardBlockAdjustmentPreview(selections[0], selections[3])) + "%c";
		con->printf(1, 8, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	}
	else
	{
		s = "%cBlock:        " + std::to_string(destroyComponent->getBlock()) + "%c";
		con->printf(1, 8, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	}


	con->setColorControl(TCOD_COLCTRL_1, selectionColorizer[0], TCODColor::black);
	if (selections[0] > 0) s = "%cStrength:     " + std::to_string(destroyComponent->getStrength()) + " +" + std::to_string(selections[0]) + "%c";
	else s = "%cStrength:     " + std::to_string(destroyComponent->getStrength()) + "%c";
	con->printf(1, 11, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, selectionColorizer[1], TCODColor::black);
	if (selections[1] > 0) s = "%cAgility:      " + std::to_string(destroyComponent->getAgility()) + " +" + std::to_string(selections[1]) + "%c";
	else s = "%cAgility:      " + std::to_string(destroyComponent->getAgility()) + "%c";
	con->printf(1, 12, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, selectionColorizer[2], TCODColor::black);
	if (selections[2] > 0) s = "%cEndurance:    " + std::to_string(destroyComponent->getEndurance()) + " +" + std::to_string(selections[2]) + "%c";
	else s = "%cEndurance:    " + std::to_string(destroyComponent->getEndurance()) + "%c";
	con->printf(1, 13, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, selectionColorizer[3], TCODColor::black);
	if (selections[3] > 0) s = "%cLuck:         " + std::to_string(destroyComponent->getLuck()) + " +" + std::to_string(selections[3]) + "%c";
	else s = "%cLuck:         " + std::to_string(destroyComponent->getLuck()) + "%c";
	con->printf(1, 14, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, selectionColorizer[4], TCODColor::black);
	if (selections[4] > 0) s = "%cIntelligence: " + std::to_string(destroyComponent->getIntelligence()) + " +" + std::to_string(selections[4]) + "%c";
	else s = "%cIntelligence: " + std::to_string(destroyComponent->getIntelligence()) + "%c";
	con->printf(1, 15, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, selectionColorizer[5], TCODColor::black);
	if (selections[5] > 0) s = "%cWisdom:       " + std::to_string(destroyComponent->getWisdom()) + " +" + std::to_string(selections[5]) + "%c";
	else s = "%cWisdom:       " + std::to_string(destroyComponent->getWisdom()) + "%c";
	con->printf(1, 16, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	con->setColorControl(TCOD_COLCTRL_1, selectionColorizer[6], TCODColor::black);
	s = "%cConfirm%c";
	con->printf(1, 17, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, 0, 0);
	delete con;
}

void drawInspectionWindow(Entity* entity)
{
	ItemComponent* itemComponent = entity->getItemComponent();
	int borderWidth = CELL_COLUMNS;
	int borderHeight = CELL_ROWS;
	TCODColor borderColor = TCOD_darker_green;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	drawBorder(con, borderHeight, borderWidth, borderColor);

	std::string s = entity->getName();
	con->printf(CELL_COLUMNS / 2 - (int)s.size() / 2, 1, s.c_str());
	wrapTextWithinBounds(con, entity->getDescription(), 5, 5, 50, 30);

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, 0, 0);
	delete con;
}

void highlightTile(int xPos, int yPos, int oldX, int oldY, Map* map, Player* player, std::vector<Entity*> entities)
{
	Tile** world = map->getWorld();
	world[oldX][oldY].setVisibleBackground(world[oldX][oldY].getStoreBackground());
	world[xPos][yPos].setStoreBackground(world[xPos][yPos].getVisibleBackground());
	world[xPos][yPos].setVisibleBackground(TCODColor::celadon);
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* entity = *it;
		if (entity->getXPos() == oldX && entity->getYPos() == oldY)
		{
			player->getPlayerAI()->setTarget(NULL);
			entity->setSpriteBackground(entity->getStoreBackground());
			continue;
		}
		if (entity->getXPos() == xPos && entity->getYPos() == yPos)
		{
			player->getPlayerAI()->setTarget(entity);
			entity->setStoreBackground(entity->getSpriteBackground());
			entity->setSpriteBackground(TCODColor::celadon);
		}
	}
}

void highlightAOETiles(int xPos, int yPos, int oldX, int oldY, int range, Map* map, Player* player, std::vector<Entity*> entities)
{
	Tile** world = map->getWorld();

	// Reset the backgrounds on the old highlighted area.
	for (int i = -range; i <= range; i++)
	{
		for (int j = -range; j <= range; j++)
		{
			world[oldX + i][oldY + j].setVisibleBackground(world[oldX + i][oldY + j].getStoreBackground());
			for (Entity* entity : entities)
			{
				if (entity->getXPos() == oldX + i && entity->getYPos() == oldY + j)
				{
					player->getPlayerAI()->setTarget(NULL);
					entity->setSpriteBackground(entity->getStoreBackground());
				}
			}
		}
	}

	// Store the original visible background.
	// Set the backgrounds on the new hightlighted area.
	for (int i = -range; i <= range; i++)
	{
		for (int j = -range; j <= range; j++)
		{
			world[xPos + i][yPos + j].setStoreBackground(world[xPos + i][yPos + j].getVisibleBackground());
			if (i == 0 && j == 0)
			{
				world[xPos + i][yPos + j].setVisibleBackground(TCODColor::brass);
			}
			else
				world[xPos + i][yPos + j].setVisibleBackground(TCODColor::celadon);
			for (Entity* entity : entities)
			{
				if (entity->getXPos() == xPos + i && entity->getYPos() == yPos + j)
				{
					player->getPlayerAI()->setTarget(entity);
					entity->setStoreBackground(entity->getSpriteBackground());
					if (i == 0 && j == 0)
					{
						entity->setSpriteBackground(TCODColor::brass);
					}
					else
						entity->setSpriteBackground(TCODColor::celadon);
				}
			}
		}
	}
}

void highlightLineTiles(int cardinalDirection, int oldCardinalDirection, int range,
							Map* map, Player* player, std::vector<Entity*> entities)
{
	Tile** world = map->getWorld();
	int xPos = player->getXPos();
	int yPos = player->getYPos();
	std::vector<int> oldXY = utilityfunctions::getCardinalDirectionXYValues(oldCardinalDirection);
	std::vector<int> newXY = utilityfunctions::getCardinalDirectionXYValues(cardinalDirection);
	int rangeX = newXY[0];
	int rangeY = newXY[1];
	int oldRangeX = oldXY[0];
	int oldRangeY = oldXY[1];

	for (int i = 0; i < range; i++)
	{
		world[xPos + oldRangeX * (1 + i)][yPos + oldRangeY * (1 + i)].setVisibleBackground(world[xPos + oldRangeX * (1 + i)][yPos + oldRangeY * (1 + i)].getStoreBackground());
	}

	for (int i = 0; i < range; i++)
	{
		world[xPos + rangeX * (1 + i)][yPos + rangeY * (1 + i)].setVisibleBackground(world[xPos + rangeX * (1 + i)][yPos + rangeY * (1 + i)].getVisibleBackground());
		world[xPos + rangeX * (1 + i)][yPos + rangeY * (1 + i)].setVisibleBackground(TCODColor::celadon);
	}
}

void highlightConeTiles(int cardinalDirection, int oldCardinalDirection, int range, int width,
	Map* map, Player* player, std::vector<Entity*> entities)
{
	Tile** world = map->getWorld();
	int xPos = player->getXPos();
	int yPos = player->getYPos();
	std::vector<int> oldXY = utilityfunctions::getCardinalDirectionXYValues(oldCardinalDirection);
	std::vector<int> newXY = utilityfunctions::getCardinalDirectionXYValues(cardinalDirection);
	int xComponent = newXY[0];
	int yComponent = newXY[1];
	int oldXComponent = oldXY[0];
	int oldYComponent = oldXY[1];

	resetConeHighlight(oldCardinalDirection, range, width,
		map, player, entities);

	if (xComponent == 0)
	{
		for (int i = 0; i < range; i++)
		{
			for (int j = -1 * (i + width); j < i + 1 + width; j++)
			{
				world[xPos + j][yPos + yComponent * (i + 1)].setVisibleBackground(TCODColor::celadon);
			}
		}
	}

	else if (yComponent == 0)
	{
		for (int i = 0; i < range; i++)
		{
			for (int j = -1 * (i + width); j < i + 1 + width; j++)
			{
				world[xPos + xComponent * (i + 1)][yPos + j].setVisibleBackground(TCODColor::celadon);
			}
		}
	}

	else if (xComponent != 0 && yComponent != 0)
	{
		for (int i = 0; i < range+1; i++)
		{
			for (int j = 0; j < range - i + 1; j++)
			{
				world[xPos + (xComponent + ((range - i - j) * xComponent))][yPos + (yComponent + ((i)*yComponent))].setVisibleBackground(TCODColor::celadon);
			}
		}
	}
}

void resetConeHighlight(int cardinalDirection, int range, int width,
	Map* map, Player* player, std::vector<Entity*> entities)
{
	Tile** world = map->getWorld();
	int xPos = player->getXPos();
	int yPos = player->getYPos();

	std::vector<int> xy = utilityfunctions::getCardinalDirectionXYValues(cardinalDirection);
	int xComponent = xy[0];
	int yComponent = xy[1];

	if (xComponent == 0)
	{
		for (int i = 0; i < range; i++)
		{
			for (int j = -1 * (i + width); j < i + 1 + width; j++)
			{
				world[xPos + j][yPos + yComponent * (i + 1)].setVisibleBackground(world[xPos + j][yPos + yComponent * (i + 1)].getStoreBackground());
			}
		}
	}

	else if (yComponent == 0)
	{
		for (int i = 0; i < range; i++)
		{
			for (int j = -1 * (i + width); j < i + 1 + width; j++)
			{
				world[xPos + xComponent * (i + 1)][yPos + j].setVisibleBackground(world[xPos + xComponent * (i + 1)][yPos + j].getStoreBackground());
			}
		}
	}

	else if (xComponent != 0 && yComponent != 0)
	{
		for (int i = 0; i < range+1; i++)
		{
			for (int j = 0; j < range - i + 1; j++)
			{
				world[xPos + (xComponent + ((range - i - j) * xComponent))][yPos + (yComponent + ((i)*yComponent))]
					.setVisibleBackground(world[xPos + (xComponent + ((range - i - j) * xComponent))][yPos + (yComponent + ((i)*yComponent))].getStoreBackground());
			}
		}
	}
}

void resetLineHighlight(int cardinalDirection, int range,
	Map* map, Player* player, std::vector<Entity*> entities)
{
	Tile** world = map->getWorld();
	int xPos = player->getXPos();
	int yPos = player->getYPos();

	std::vector<int> xy = utilityfunctions::getCardinalDirectionXYValues(cardinalDirection);
	for (int i = 0; i <= range; i++)
	{
		world[xPos + xy[0] * (1 + i)][yPos + xy[1] * (1 + i)].setVisibleBackground(world[xPos + xy[0] * (1 + i)][yPos + xy[1] * (1 + i)].getStoreBackground());
	}

}

void resetHighlight(int xPos, int yPos, Map* map, Player* player, std::vector<Entity*> entities)
{
	Tile** world = map->getWorld();
	world[xPos][yPos].setVisibleBackground(world[xPos][yPos].getStoreBackground());
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* entity = *it;
		if (entity->getXPos() == xPos && entity->getYPos() == yPos)
		{
			player->getPlayerAI()->setTarget(NULL);
			entity->setSpriteBackground(entity->getStoreBackground());
			return;
		}
	}
}

void resetAOEHighlight(int xPos, int yPos, int range, Map* map, Player* player, std::vector<Entity*> entities)
{
	Tile** world = map->getWorld();
	for (int i = -range; i <= range; i++)
	{
		for (int j = -range; j <= range; j++)
		{
			world[xPos+i][yPos+j].setVisibleBackground(world[xPos+i][yPos+j].getStoreBackground());
			for (Entity* entity : entities)
			{
				if (entity->getXPos() == xPos + i && entity->getYPos() == yPos + j)
				{
					player->getPlayerAI()->setTarget(NULL);
					entity->setSpriteBackground(entity->getStoreBackground());
				}
			}
		}
	}
}

void wrapTextWithinBounds(TCODConsole* con, std::string s, int x_1, int y_1, int x_2, int y_2)
{
	std::stringstream ss(s);
	int positionPointer = 0;
	int y = 0;
	do
	{
		std::string word;
		ss >> word;
		if (positionPointer + word.size() >= x_2)
		{
			positionPointer = 0;
			y++;
		}
		con->printf(x_1 + positionPointer, y_1 + y, word.c_str());
		positionPointer += (int)word.size();
		positionPointer++;
	} while (ss);
}

void animateCellOnTimer(int xPos, int yPos, Map* map, Player* player, std::vector<Entity*> entities)
{
	std::time_t result = std::time(nullptr);
	std::localtime(&result);
	if (result >= engine->getTime() + 1 && player->getSpriteBackground() == TCODColor::black)
	{
		player->setSpriteBackground(TCODColor::brass);
		engine->setTime(result);
	}
	else if (result >= engine->getTime() + 1 && player->getSpriteBackground() == TCODColor::brass)
	{
		player->setSpriteBackground(TCODColor::black);
		engine->setTime(result);
	}
}

void animateAuraAroundCell(int xPos, int yPos)
{
	std::time_t result = std::time(nullptr);
	std::localtime(&result);
	Tile** world = engine->getMap()->getWorld();
	if (result >= engine->getTime() + 1)
	{
		//if ()
		for (int i = -1; i <= 1; i++)
		{
			world[xPos + i][yPos - 1].setVisibleBackground(TCODColor::darkRed);
		}
	}
}

void drawUI()
{
	TCODConsole::root->clear();
	drawUtilityWindow();
	drawTargetWindow();
	drawLogWindow();
	drawMainBorder();
	drawMainWindow(engine->getMap(), engine->getPlayer(), engine->getEntities());
	TCODConsole::flush();
}