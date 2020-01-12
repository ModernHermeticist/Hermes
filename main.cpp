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
		Engine::STATE currentGameState = engine->getState();
		Engine::STATE newGameState = currentGameState;
		if (currentGameState == Engine::STATE::PLAYER_TURN)
		{ 
			TCOD_key_t key;
			TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
			if (key.vk == TCODK_ESCAPE) break;
			engine->setLastKey(key);
			newGameState = engine->getPlayer()->Update();
			engine->setRefresh(true);
		}

		if (currentGameState == Engine::STATE::ENEMY_TURN)
		{
			newGameState = engine->updateEntities();
			engine->setRefresh(true);
		}
		
		if (currentGameState == Engine::STATE::SHOW_CHARACTER_SCREEN)
		{
			TCODConsole::root->clear();
			drawCharacterWindow();
			TCODConsole::flush();
			while (true)
			{
				TCOD_key_t key;
				TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
				if (key.vk != 0 && key.c == 'c')
				{
					break;
				}
			}
			engine->setRefresh(true);
			newGameState = Engine::STATE::PLAYER_TURN;
		}

		if (currentGameState == Engine::STATE::SHOW_INVENTORY_SCREEN)
		{
			TCODConsole::root->clear();
			drawInventoryWindow();
			TCODConsole::flush();
			while (true)
			{
				TCOD_key_t key;
				TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
				if (key.vk == TCODK_CHAR)
				{
					if (key.lctrl)
					{
						newGameState = engine->getPlayer()->getPlayerAI()->dropItem(key.c);
						engine->setRefresh(true);
					}
					else if (key.shift)
					{
						newGameState = engine->getPlayer()->getPlayerAI()->equipItem(key.c);
						engine->setRefresh(true);
					}
					/*else if (key.lalt)
					{
						newGameState = engine->getPlayer()->getPlayerAI()->inspectItem(key.c);
						engine->setRefresh(true);
					}*/
					else
					{
						newGameState = engine->getPlayer()->getPlayerAI()->useItem(key.c);
						engine->setRefresh(true);
					}
				}
				else if (key.vk == TCODK_ESCAPE)
				{
					engine->setRefresh(true);
					newGameState = Engine::STATE::PLAYER_TURN;
				}
			}
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
		engine->setState(newGameState);
	}
	delete engine;
	return 0;
}





