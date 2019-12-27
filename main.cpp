#include "main.h"

Engine* engine;

int main() 
{
	srand(time(NULL));
	TCODSystem::forceFullscreenResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	TCODConsole::initRoot(CELL_COLUMNS, CELL_ROWS, "Hermes", false, TCOD_RENDERER_GLSL);
	TCODConsole::setCustomFont("sirhenry.png", TCOD_FONT_LAYOUT_ASCII_INCOL);

	engine = new Engine(CELL_COLUMNS, CELL_ROWS, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

	engine->loadMapFile("test.xp");

	TCODConsole::root->clear();

	engine->getMap()->computeFov();

	drawUtilityWindow();
	drawLogWindow();
	drawMainBorder();
	drawMainWindow(engine->getMap(), engine->getPlayer(), engine->getEntities());
	TCODConsole::flush();
	
	while (!TCODConsole::isWindowClosed())
	{
		bool refresh = false;
		TCOD_key_t key;
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
		engine->setLastKey(key);
		if (key.vk != 0 && engine->turn == Engine::TURN::PLAYER_TURN)
		{
			if (key.vk == TCODK_ESCAPE) break;
			engine->getPlayer()->Update();
			engine->turn = Engine::TURN::ENEMY_TURN;
			refresh = true;
		}

		if (engine->turn == Engine::TURN::ENEMY_TURN)
		{
			engine->updateEntities();
			engine->turn = Engine::TURN::PLAYER_TURN;
		}

		if (refresh)
		{
			if (engine->getComputeFov())
			{
				engine->getMap()->computeFov();
				engine->setComputeFov(false);
			}

			TCODConsole::root->clear();
			drawUtilityWindow();
			drawLogWindow();
			drawMainBorder();
			drawMainWindow(engine->getMap(), engine->getPlayer(), engine->getEntities());
			TCODConsole::flush();
		}
	}
	delete engine;
	return 0;
}





