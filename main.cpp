#include "main.h"


int main() 
{
	int xPos = CELL_COLUMNS / 2;
	int yPos = CELL_ROWS / 2;
	TCODSystem::setFps(60);
	TCODSystem::forceFullscreenResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	TCODConsole::initRoot(CELL_COLUMNS, CELL_ROWS, "Hermes", true, TCOD_RENDERER_GLSL);
	TCODConsole::setCustomFont("sirhenry.png", TCOD_FONT_LAYOUT_ASCII_INCOL);
	Player* player = new Player(xPos, yPos);


	xp::RexImage test("test.xp");
	test.flatten();

	

	TCODConsole::root->clear();

	for (int i = 0; i < test.getWidth(); i++)
	{
		for (int j = 0; j < test.getHeight(); j++)
		{
			xp::RexTile t = *test.getTile(0, i, j);
			TCODColor c = TCOD_black;
			c.r = t.fore_red;
			c.b = t.fore_blue;
			c.g = t.fore_green;

			TCODConsole::root->putCharEx(i, j, t.character, c, TCOD_black);
		}
	}

	

	TCODConsole::root->putChar(player->getXPos(), player->getYPos(), '@');
	TCODConsole::flush();

	
	while (!TCODConsole::isWindowClosed())
	{
		bool refresh = false;
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		if (key.vk != NULL)
		{
			if (key.vk == TCODK_ESCAPE) break;
			player->Update(key);
			refresh = true;
		}

		if (refresh)
		{
			TCODConsole::root->clear();
			for (int i = 0; i < test.getWidth(); i++)
			{
				for (int j = 0; j < test.getHeight(); j++)
				{
					xp::RexTile t = *test.getTile(0, i, j);
					TCODColor c = TCOD_black;
					c.r = t.fore_red;
					c.b = t.fore_blue;
					c.g = t.fore_green;
					
					TCODConsole::root->putCharEx(i, j, t.character, c, TCOD_black);
				}
			}
			TCODConsole::root->putChar(player->getXPos(), player->getYPos(), '@');
			TCODConsole::flush();
		}
	}
	delete player;
	return 0;
}