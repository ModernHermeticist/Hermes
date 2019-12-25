#include "main.h"

void drawMainBorder()
{
	int borderWidth = MAIN_WINDOW_WIDTH;
	int borderHeight = MAIN_WINDOW_HEIGHT;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	con->putCharEx(0, 0, TOP_FORK_WALL, TCOD_white, TCOD_black);
	con->putCharEx(0, borderHeight-1, LEFT_FORK_WALL, TCOD_white, TCOD_black);
	con->putCharEx(borderWidth-1, 0, TOP_RIGHT_CORNER_WALL, TCOD_white, TCOD_black);
	con->putCharEx(borderWidth - 1, borderHeight-1, RIGHT_FORK_WALL, TCOD_white, TCOD_black);
	for (int i = 1; i < borderWidth-1; i++)
	{
		con->putCharEx(i, 0, HORIZONTAL_WALL, TCOD_white, TCOD_black);
		con->putCharEx(i, borderHeight-1, HORIZONTAL_WALL, TCOD_white, TCOD_black);
	}
	for (int i = 1; i < borderHeight-1; i++)
	{
		con->putCharEx(0, i, VERTICAL_WALL, TCOD_white, TCOD_black);
		con->putCharEx(borderWidth-1, i, VERTICAL_WALL, TCOD_white, TCOD_black);
	}

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, CELL_COLUMNS - borderWidth, 0);
	delete con;
}

void drawMainWindow(Tile** tiles, Player* player, std::vector<Entity*> entities)
{
	int borderWidth = MAIN_WINDOW_WIDTH - 2;
	int borderHeight = MAIN_WINDOW_HEIGHT - 2;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);

	int width = engine->getWorldWidth();
	int height = engine->getWorldHeight();
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Tile tile = tiles[x][y];
			con->putCharEx(tile.getXPos(), tile.getYPos(), tile.getSprite(), tile.getForeground(), tile.getBackground());
		}
	}
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* entity = *it;
		con->putCharEx(entity->getXPos(), entity->getYPos(), entity->getSprite(), entity->getSpriteForeground(), entity->getSpriteBackground());
	}
	con->putChar(player->getXPos(), player->getYPos(), player->getSprite());
	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, CELL_COLUMNS - borderWidth-1, 1);
	delete con;
}

void drawUtilityWindow()
{
	int borderWidth = UTILITY_WINDOW_WIDTH;
	int borderHeight = UTILITY_WINDOW_HEIGHT;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);

	con->putCharEx(0, 0, TOP_LEFT_CORNER_WALL, TCOD_white, TCOD_black);
	con->putCharEx(0, borderHeight - 1, BOTTOM_LEFT_CORNER_WALL, TCOD_white, TCOD_black);
	con->putCharEx(borderWidth - 1, 0, TOP_RIGHT_CORNER_WALL, TCOD_white, TCOD_black);
	con->putCharEx(borderWidth - 1, borderHeight - 1, BOTTOM_RIGHT_CORNER_WALL, TCOD_white, TCOD_black);

	for (int i = 1; i < borderWidth-1; i++)
	{
		con->putCharEx(i, 0, HORIZONTAL_WALL, TCOD_white, TCOD_black);
		con->putCharEx(i, borderHeight - 1, HORIZONTAL_WALL, TCOD_white, TCOD_black);
	}
	for (int i = 1; i < borderHeight-1; i++)
	{
		con->putCharEx(0, i, VERTICAL_WALL, TCOD_white, TCOD_black);
		con->putCharEx(borderWidth - 1, i, VERTICAL_WALL, TCOD_white, TCOD_black);
	}

	con->printf(1, 1, "Hello world!");

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, 0, 0);
	delete con;
}

void drawLogWindow()
{
	int borderWidth = LOG_WINDOW_WIDTH;
	int borderHeight = LOG_WINDOW_HEIGHT;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);

	con->putCharEx(0, 0, TOP_LEFT_CORNER_WALL, TCOD_white, TCOD_black);
	con->putCharEx(0, borderHeight - 1, BOTTOM_FORK_WALL, TCOD_white, TCOD_black);
	con->putCharEx(borderWidth - 1, 0, RIGHT_FORK_WALL, TCOD_white, TCOD_black);
	con->putCharEx(borderWidth - 1, borderHeight - 1, BOTTOM_RIGHT_CORNER_WALL, TCOD_white, TCOD_black);

	for (int i = 1; i < borderWidth - 1; i++)
	{
		con->putCharEx(i, 0, HORIZONTAL_WALL, TCOD_white, TCOD_black);
		con->putCharEx(i, borderHeight - 1, HORIZONTAL_WALL, TCOD_white, TCOD_black);
	}
	for (int i = 1; i < borderHeight - 1; i++)
	{
		con->putCharEx(0, i, VERTICAL_WALL, TCOD_white, TCOD_black);
		con->putCharEx(borderWidth - 1, i, VERTICAL_WALL, TCOD_white, TCOD_black);
	}

	std::vector<std::string> log = engine->getLog();
	for (int i = 0; i < log.size(); i++)
	{
		con->printf(1, i + 1, log[i].c_str());
	}

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, CELL_COLUMNS - borderWidth, MAIN_WINDOW_HEIGHT-1);
	delete con;
}