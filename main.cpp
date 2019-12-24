#include "main.h"


int main() 
{
	int xPos = 21;
	int yPos = 20;
	TCODSystem::setFps(60);
	TCODSystem::forceFullscreenResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	TCODConsole::initRoot(CELL_COLUMNS, CELL_ROWS, "Hermes", true, TCOD_RENDERER_GLSL);
	TCODConsole::setCustomFont("sirhenry.png", TCOD_FONT_LAYOUT_ASCII_INCOL);
	Player* player = new Player(xPos, yPos);


	xp::RexImage test("test.xp");
	test.flatten();

	std::vector<Tile*> tiles;

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

			Tile* tile = new Tile(i, j, t.character, c, TCOD_black);
			int sprite = tile->getSprite();

			if (sprite == 192 || sprite == 179 || sprite == 191 || sprite == 196 || sprite == 217 || sprite == 218)
			{
				tile->setWalkable(false);
				tile->setBlocks(true);
			}

			tiles.push_back(tile);
		}
	}

	
	drawMainBorder();
	drawMainWindow(tiles, player);
	TCODConsole::flush();

	
	while (!TCODConsole::isWindowClosed())
	{
		bool refresh = false;
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		if (key.vk != NULL)
		{
			if (key.vk == TCODK_ESCAPE) break;
			player->Update(key, tiles);
			refresh = true;
		}

		if (refresh)
		{
			TCODConsole::root->clear();

			drawMainBorder();
			drawMainWindow(tiles, player);
			TCODConsole::flush();
		}
	}
	delete player;
	return 0;
}