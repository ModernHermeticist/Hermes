#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <time.h>


#include <libtcod.hpp>
#include "REXSpeeder.h"

#include "Tile.h"
#include "Map.h"
#include "Entity.h"
#include "Player.h"
#include "gui.h"
#include "LogEntry.h"
#include "Engine.h"


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int CELL_COLUMNS = SCREEN_WIDTH / 20;
const int CELL_ROWS = SCREEN_HEIGHT / 20;

const int MAIN_WINDOW_WIDTH = 75; //THE PLAY AREA IS 73 WIDE
const int MAIN_WINDOW_HEIGHT = 46; //THE PLAY AREA IS 52 HIGH
const int UTILITY_WINDOW_WIDTH = 22;
const int UTILITY_WINDOW_HEIGHT = 54;
const int LOG_WINDOW_WIDTH = 75;
const int LOG_WINDOW_HEIGHT = 9;

const int TOP_LEFT_CORNER_WALL = 218;
const int BOTTOM_RIGHT_CORNER_WALL = 217;
const int VERTICAL_WALL = 179;
const int TOP_RIGHT_CORNER_WALL = 191;
const int BOTTOM_LEFT_CORNER_WALL = 192;
const int HORIZONTAL_WALL = 196;
const int TOP_FORK_WALL = 194;
const int BOTTOM_FORK_WALL = 193;
const int LEFT_FORK_WALL = 195;
const int RIGHT_FORK_WALL = 180;

const int WATER = '~';

#endif