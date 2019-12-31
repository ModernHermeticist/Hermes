#ifndef GUI_H
#define GUI_H

void drawMainBorder();
void drawMainWindow(Map* map, Player* player, std::vector<Entity*> entities);
void drawUtilityWindow();
void drawLogWindow();
void drawBorder(TCODConsole* con, int borderHeight, int borderWidth, TCODColor borderColor);
void drawCharacterWindow();
void drawInventoryWindow();
void drawProgressionWindow();

#endif