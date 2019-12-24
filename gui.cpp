#include "main.h"

void drawMainBorder()
{
	int borderWidth = MAIN_WINDOW_WIDTH;
	int borderHeight = MAIN_WINDOW_HEIGHT;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	for (int i = 0; i < borderWidth; i++)
	{
		con->putCharEx(i, 0, '*', TCOD_white, TCOD_black);
		con->putCharEx(i, borderHeight-1, '*', TCOD_white, TCOD_black);
	}
	for (int i = 0; i < borderHeight; i++)
	{
		con->putCharEx(0, i, '*', TCOD_white, TCOD_black);
		con->putCharEx(borderWidth-1, i, '*', TCOD_white, TCOD_black);
	}

	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, CELL_COLUMNS - borderWidth, 0);
	delete con;
}

void drawMainWindow(std::vector<Tile*> tiles, Player* player)
{
	int borderWidth = MAIN_WINDOW_WIDTH - 2;
	int borderHeight = MAIN_WINDOW_HEIGHT - 2;
	TCODConsole* con = new TCODConsole(borderWidth, borderHeight);
	int size = tiles.size();
	for (int i = 0; i < size; i++)
	{
		Tile* tile = tiles[i];
		con->putCharEx(tile->getXPos(), tile->getYPos(), tile->getSprite(), tile->getForeground(), tile->getBackground());
	}
	con->putChar(player->getXPos(), player->getYPos(), '@');
	TCODConsole::blit(con, 0, 0, borderWidth, borderHeight, TCODConsole::root, CELL_COLUMNS - borderWidth-1, 1);
	delete con;
}