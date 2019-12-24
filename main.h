#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <vector>

#include <libtcod.hpp>
#include "REXSpeeder.h"

#include "Tile.h"
#include "Player.h"
#include "gui.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int CELL_COLUMNS = SCREEN_WIDTH / 20;
//const int CELL_COLUMNS = 60;
const int CELL_ROWS = SCREEN_HEIGHT / 20;
//const int CELL_ROWS = 60;

const int MAIN_WINDOW_WIDTH = 75;
const int MAIN_WINDOW_HEIGHT = 54;

#endif