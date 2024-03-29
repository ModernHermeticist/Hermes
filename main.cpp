#include "main.h"

Engine* engine;

int main() 
{
	TTF_Init();
	srand((unsigned int)time(NULL));
	TCOD_sys_force_fullscreen_resolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	TCODConsole::setCustomFont("Bisasam_16x16.png", TCOD_FONT_LAYOUT_ASCII_INROW, 16, 18);
	TCODConsole::initRoot(CELL_COLUMNS, CELL_ROWS, "Hermes", false, TCOD_RENDERER_SDL2);
	TCODSystem::setFps(30);

	engine = new Engine(CELL_COLUMNS, CELL_ROWS, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

	engine->loadMapFile("test.xp");

	engine->getMap()->computeFov();

	drawUI();
	
	while (!TCODConsole::isWindowClosed())
	{
		Engine::STATE currentGameState = engine->getState();
		Engine::STATE newGameState = currentGameState;
		if (currentGameState == Engine::STATE::PLAYER_TURN)
		{ 
			TCOD_key_t key;
			TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
			if (key.vk == TCODK_ESCAPE) break;
			engine->setLastKey(key);
			newGameState = engine->getPlayer()->Update();
			engine->setRefresh(true);
		}

		else if (currentGameState == Engine::STATE::ENEMY_TURN)
		{
			newGameState = engine->updateEntities();
			engine->setRefresh(true);
		}
		
		else if (currentGameState == Engine::STATE::SHOW_CHARACTER_SCREEN)
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

		else if (currentGameState == Engine::STATE::SHOW_INVENTORY_SCREEN)
		{
			TCODConsole::root->clear();
			drawInventoryWindow();
			TCODConsole::flush();
			bool show = true;
			while (show)
			{
				TCOD_key_t key;
				TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
				engine->setLastKey(key);
				if (key.vk == TCODK_CHAR)
				{
					if (key.lctrl)
					{
						newGameState = engine->getPlayer()->getPlayerAI()->dropItem(key.c);
						engine->setRefresh(true);
						show = false;
					}
					else if (key.shift)
					{
						newGameState = engine->getPlayer()->getPlayerAI()->equipItem(key.c);
						engine->setRefresh(true);
						show = false;
					}
					else if (key.lalt)
					{
						newGameState = Engine::STATE::INSPECT_ITEM;
						show = false;
					}
					else
					{
						newGameState = engine->getPlayer()->getPlayerAI()->useItem(key.c);
						engine->setRefresh(true);
						show = false;
					}
				}
				else if (key.vk == TCODK_ESCAPE)
				{
					engine->setRefresh(true);
					newGameState = Engine::STATE::PLAYER_TURN;
					show = false;
				}
			}
		}

		else if (currentGameState == Engine::STATE::PICK_UP_ITEM)
		{
			newGameState = engine->getPlayer()->getPlayerAI()->pickUpItem();
			engine->setRefresh(true);
		}

		else if (currentGameState == Engine::STATE::INSPECT_ITEM)
		{
			newGameState = engine->getPlayer()->getPlayerAI()->inspectItem(engine->getLastKey().c);
			engine->setRefresh(true);
		}

		else if (currentGameState == Engine::STATE::PROGRESS_CHARACTER)
		{
			newGameState = engine->getPlayer()->getPlayerAI()->progressCharacter();
			engine->setRefresh(true);
		}
		engine->updateEntityAnimations();
		if (engine->getComputeFov())
		{
			engine->getMap()->computeFov();
			engine->setComputeFov(false);
		}
		drawUI();
		engine->setState(newGameState);
	}
	delete engine;

	TTF_Quit();
	return 0;
}





