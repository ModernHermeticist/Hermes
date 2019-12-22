#pragma once

#include <iostream>
#include <string>

#include "BearLibTerminal/Include/C/BearLibTerminal.h"
#include "libtcod/include/libtcod.hpp"
#include "libtcod/include/libtcod/tileset/truetype.h"


int font_size = 16;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
int cell_columns = SCREEN_WIDTH / 20;
int cell_rows = SCREEN_HEIGHT / 20;