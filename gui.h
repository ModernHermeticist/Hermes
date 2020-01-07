#ifndef GUI_H
#define GUI_H

void drawMainBorder();
void drawMainWindow(Map* map, Player* player, std::vector<Entity*> entities);
void drawUtilityWindow();
void drawTargetWindow();
void drawLogWindow();
void drawBorder(TCODConsole* con, int borderHeight, int borderWidth, TCODColor borderColor);
void drawCharacterWindow();
void drawInventoryWindow();
void drawProgressionWindow(std::vector<int> selections, std::vector<TCODColor> selectionColorizer);
void drawInspectionWindow(Entity* entity);
void highlightTile(int xPos, int yPos, int oldX, int oldY, Map* map, Player* player, std::vector<Entity*> entities);
void highlightAOETiles(int xPos, int yPos, int oldX, int oldY, int range, Map* map, Player* player, std::vector<Entity*> entities);
void highlightLineTiles(int cardinalDirection, int oldCardinalDirection, int range,
	Map* map, Player* player, std::vector<Entity*> entities);
void highlightConeTiles(int cardinalDirection, int oldCardinalDirection, int range,
	Map* map, Player* player, std::vector<Entity*> entities);
void resetHighlight(int xPos, int yPos, Map* map, Player* player, std::vector<Entity*> entities);
void resetAOEHighlight(int xPos, int yPos, int range, Map* map, Player* player, std::vector<Entity*> entities);
void resetLineHighlight(int cardinalDirection, int range,
	Map* map, Player* player, std::vector<Entity*> entities);

void wrapTextWithinBounds(TCODConsole* con, std::string s, int x_1, int y_1, int x_2, int y_2);

void drawUI();

#endif