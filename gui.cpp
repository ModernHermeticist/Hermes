#include "main.h"

void drawMainBorder()
{
	int borderWidth = MAIN_WINDOW_WIDTH;
	int borderHeight = MAIN_WINDOW_HEIGHT;
	TCODColor borderColor = TCOD_darker_green;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	con->putCharEx(0, 0, TOP_FORK_WALL, borderColor, TCOD_black);
	con->putCharEx(0, borderHeight-1, LEFT_FORK_WALL, borderColor, TCOD_black);
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

	std::vector<LogEntry> log = engine->getLog();
	for (int i = 0; i < log.size(); i++)
	{
		LogEntry entry = log[i];
		std::string s = entry.getEntry();
		for (int k = 0; k < s.size(); k++)
		{
			con->putCharEx(k + 1, i + 1, s[k], entry.getEntryColor(), TCOD_black);
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
	con->printf(CELL_COLUMNS / 2 - s.size() / 2, 1, s.c_str());
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
	int size = storage.size();

	int borderWidth = CELL_COLUMNS;
	int borderHeight = CELL_ROWS;
	TCODColor borderColor = TCOD_darker_green;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	drawBorder(con, borderHeight, borderWidth, borderColor);
	std::string s = "Inventory";
	std::stringstream ss;
	con->printf(CELL_COLUMNS / 2 - s.size() / 2, 1, s.c_str());
	con->printf(1, CELL_ROWS - 2, "Use item: (letter)    Equip item: (shift+letter)    Drop item: (ctrl+letter)");
	if (storage.size() > 0)
	{
		for (int i = 0; i < size; i++)
		{
			char label = 97 + i;
			if (storage[i]->getItemComponent()->isEquipped())
				ss << label << ") " << storage[i]->getName() << " (e)";
			else ss << label << ") " << storage[i]->getName();
			con->printf(1, i + 2, ss.str().c_str());
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

void drawProgressionWindow()
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
	std::stringstream ss;
	con->printf(CELL_COLUMNS / 2 - s.size() / 2, 1, s.c_str());
	con->setColorControl(TCOD_COLCTRL_1, TCODColor::grey, TCODColor::black);
	s = "%cHealth:       " + std::to_string(destroyComponent->getCurrentHealth()) + '/' +
		std::to_string(destroyComponent->getMaximumHealth()) + "%c";
	con->printf(1, 3, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	s = "%cStamina:      " + std::to_string(destroyComponent->getCurrentStamina()) + '/' +
		std::to_string(destroyComponent->getMaximumStamina()) + "%c";
	con->printf(1, 4, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	s = "%cMana:         " + std::to_string(destroyComponent->getCurrentMana()) + '/' +
		std::to_string(destroyComponent->getMaximumMana()) + "%c";
	con->printf(1, 5, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	s = "%cDamage:       " + std::to_string(attackComponent->getMinimumAttackPower()) + '-' +
		std::to_string(attackComponent->getMaximumAttackPower()) + "%c";
	con->printf(1, 6, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	s = "%cArmor:        " + std::to_string(destroyComponent->getArmor()) + "%c";
	con->printf(1, 7, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	s = "%cBlock:        " + std::to_string(destroyComponent->getBlock()) + "%c";
	con->printf(1, 8, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	s = "%cDodge:        " + std::to_string(destroyComponent->getDodge()) + "%c";
	con->printf(1, 9, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	s = "%cParry:        " + std::to_string(destroyComponent->getParry()) + "%c";
	con->printf(1, 10, s.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

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

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, 0, 0);
	delete con;
}