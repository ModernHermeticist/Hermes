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

	engine->getMap()->computeFov();

	drawUtilityWindow();
	drawLogWindow();
	drawMainBorder();
	drawMainWindow(engine->getMap(), engine->getPlayer(), engine->getEntities());

	TCODConsole::flush();
	
	while (!TCODConsole::isWindowClosed())
	{
		engine->setRefresh(false);
		TCOD_key_t key;
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
		engine->setLastKey(key);
		if (key.vk != 0 && engine->getState() == Engine::STATE::PLAYER_TURN)
		{
			if (key.vk == TCODK_ESCAPE) break;
			engine->getPlayer()->Update();
			engine->setState(Engine::STATE::ENEMY_TURN);
		}

		if (engine->getState() == Engine::STATE::ENEMY_TURN)
		{
			engine->updateEntities();
			engine->setState(Engine::STATE::PLAYER_TURN);
		}
		
		if (engine->getState() == Engine::STATE::SHOW_CHARACTER_SCREEN && key.c == 'c')
		{
			engine->setRefresh(true);
			engine->setState(Engine::STATE::PLAYER_TURN);
		}

		if (engine->getState() == Engine::STATE::SHOW_INVENTORY_SCREEN && key.c == 'i')
		{
			engine->getPlayer()->getPlayerAI()->dropItem(key.c);
			engine->setRefresh(true);
			engine->setState(Engine::STATE::PLAYER_TURN);
		}

		if (engine->getRefresh())
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





