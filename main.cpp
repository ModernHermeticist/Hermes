#include "main.h"


int main() 
{
	int xPos = cell_columns / 2;
	int yPos = cell_rows / 2;
	TCODSystem::setFps(60);
	TCODSystem::forceFullscreenResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	TCODConsole::initRoot(cell_columns, cell_rows, "libtcod C++ tutorial", true, TCOD_RENDERER_GLSL);
	TCODConsole::setCustomFont("sirhenry.png", TCOD_FONT_LAYOUT_ASCII_INCOL);

	TCODConsole::root->clear();
	TCODConsole::root->putChar(xPos, yPos, '@');
	TCODConsole::flush();
	
	while (!TCODConsole::isWindowClosed())
	{
		bool refresh = false;
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		if (key.vk == TCODK_KP4 && xPos > 0)
		{
			xPos -= 1;
			refresh = true;
		}
		else if (key.vk == TCODK_KP6 && xPos < cell_columns - 1)
		{
			xPos += 1;
			refresh = true;
		}
		else if (key.vk == TCODK_KP8 && yPos > 0)
		{
			yPos -= 1;
			refresh = true;
		}
		else if (key.vk == TCODK_KP2 && yPos < cell_rows - 1)
		{
			yPos += 1;
			refresh = true;
		}
		else if (key.vk == TCODK_ESCAPE) break;

		if (refresh)
		{
			TCODConsole::root->clear();
			TCODConsole::root->putChar(xPos, yPos, '@');
			TCODConsole::flush();
		}
	}
	return 0;
}