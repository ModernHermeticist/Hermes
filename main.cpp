#include "main.h"

Engine* engine;

int main() 
{
	srand((unsigned int)time(NULL));
	TCODSystem::forceFullscreenResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	TCODConsole::setCustomFont("Bisasam_16x16.png", TCOD_FONT_LAYOUT_ASCII_INROW);
	TCODConsole::initRoot(CELL_COLUMNS, CELL_ROWS, "Hermes", false, TCOD_RENDERER_SDL2);

	engine = new Engine(CELL_COLUMNS, CELL_ROWS, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

	engine->loadMapFile("test.xp");

	engine->getMap()->computeFov();

	drawUI();
	
	while (!TCODConsole::isWindowClosed())
	{
		engine->setRefresh(false);
		TCOD_key_t key;
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
		engine->setLastKey(key);
		Engine::STATE currentGameState = engine->getState();
		if (key.vk != 0 && currentGameState == Engine::STATE::PLAYER_TURN)
		{
			if (key.vk == TCODK_ESCAPE) break;
			engine->getPlayer()->Update();
			key.vk = (TCOD_keycode_t)0;
		}

		currentGameState = engine->getState();
		if (currentGameState == Engine::STATE::ENEMY_TURN)
		{
			engine->updateEntities();
			engine->setState(Engine::STATE::PLAYER_TURN);
		}
		
		currentGameState = engine->getState();
		if (currentGameState == Engine::STATE::SHOW_CHARACTER_SCREEN && key.vk != 0 && key.c == 'c')
		{
			engine->setRefresh(true);
			engine->setState(Engine::STATE::PLAYER_TURN);
			key.vk = (TCOD_keycode_t)0;
		}

		currentGameState = engine->getState();
		if (currentGameState == Engine::STATE::SHOW_INVENTORY_SCREEN && key.vk != 0 && key.vk != TCODK_SHIFT && key.vk != TCODK_CONTROL && key.vk != TCODK_ALT)
		{
			if (key.vk == TCODK_CHAR)
			{
				if (key.lctrl)
					engine->getPlayer()->getPlayerAI()->dropItem(key.c);
				else if (key.shift)
					engine->getPlayer()->getPlayerAI()->equipItem(key.c);
				else if (key.lalt)
					engine->getPlayer()->getPlayerAI()->inspectItem(key.c);
				else
				{
					engine->getPlayer()->getPlayerAI()->useItem(key.c);
				}
			}
			else if (key.vk == TCODK_ESCAPE)
			{
				engine->setRefresh(true);
				engine->setState(Engine::STATE::PLAYER_TURN);
			}
			key.vk = (TCOD_keycode_t)0;
		}


		if (engine->getRefresh())
		{
			if (engine->getComputeFov())
			{
				engine->getMap()->computeFov();
				engine->setComputeFov(false);
			}

			drawUI();
		}
	}
	delete engine;
	return 0;
}





