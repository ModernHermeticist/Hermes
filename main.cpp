#include "main.h"

Engine* engine;

int main() 
{
	srand(time(NULL));
	TCODSystem::forceFullscreenResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	TCODConsole::initRoot(CELL_COLUMNS, CELL_ROWS, "Hermes", true, TCOD_RENDERER_GLSL);
	TCODConsole::setCustomFont("sirhenry.png", TCOD_FONT_LAYOUT_ASCII_INCOL);

	engine = new Engine(CELL_COLUMNS, CELL_ROWS, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

	engine->loadMapFile("test.xp");

	TCODConsole::root->clear();


	drawUtilityWindow();
	drawLogWindow();
	drawMainBorder();
	drawMainWindow(engine->getWorld(), engine->getPlayer(), engine->getEntities());
	TCODConsole::flush();

	
	while (!TCODConsole::isWindowClosed())
	{
		bool refresh = false;
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		if (key.vk != NULL)
		{
			if (key.vk == TCODK_ESCAPE) break;
			engine->getPlayer()->Update(key, engine->getWorld());
			refresh = true;
		}

		if (refresh)
		{
			engine->updateEntities();

			TCODConsole::root->clear();
			drawUtilityWindow();
			drawLogWindow();
			drawMainBorder();
			drawMainWindow(engine->getWorld(), engine->getPlayer(), engine->getEntities());
			TCODConsole::flush();
		}
	}
	delete engine;
	return 0;
}





