#ifndef CONSTANTS_H
#define CONSTANTS_H

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int CELL_COLUMNS = SCREEN_WIDTH / 20;
const int CELL_ROWS = SCREEN_HEIGHT / 20;


const int LOG_FONT_SIZE = 12;

const int MAIN_WINDOW_WIDTH = 75; //THE PLAY AREA IS 73 WIDE
const int MAIN_WINDOW_HEIGHT = 46; //THE PLAY AREA IS 52 HIGH
const int UTILITY_WINDOW_WIDTH = 22;
const int UTILITY_WINDOW_HEIGHT = 54;
const int GENERAL_LOG_WINDOW_WIDTH = 38;
const int GENERAL_LOG_WINDOW_HEIGHT = 9;
const int COMBAT_LOG_WINDOW_WIDTH = 37;
const int COMBAT_LOG_WINDOW_HEIGHT = 9;

const int GENERAL_LOG_WINDOW_TOP = int(SCREEN_HEIGHT * 0.845);
const int GENERAL_LOG_WINDOW_BOTTOM = int(SCREEN_HEIGHT * 0.96);

const int GENERAL_LOG_WINDOW_LEFT = int(SCREEN_WIDTH * 0.23);
const int GENERAL_LOG_WINDOW_RIGHT = int(SCREEN_WIDTH * 0.50);

const int COMBAT_LOG_WINDOW_TOP = int(SCREEN_HEIGHT * 0.845);
const int COMBAT_LOG_WINDOW_BOTTOM = int(SCREEN_HEIGHT * 0.96);

const int COMBAT_LOG_WINDOW_LEFT = int(SCREEN_WIDTH * 0.615);
const int COMBAT_LOG_WINDOW_RIGHT = int(SCREEN_WIDTH * 0.96);

const int TOP_LEFT_CORNER_WALL = 218;
const int BOTTOM_RIGHT_CORNER_WALL = 217;
const int VERTICAL_WALL = 179;
const int TOP_RIGHT_CORNER_WALL = 191;
const int BOTTOM_LEFT_CORNER_WALL = 192;
const int HORIZONTAL_WALL = 196;
const int CROSS_WALL = 197;
const int TOP_FORK_WALL = 194;
const int BOTTOM_FORK_WALL = 193;
const int LEFT_FORK_WALL = 195;
const int RIGHT_FORK_WALL = 180;

const int NUMBER_OF_LOG_LINES = 12;
const int MAXIMUM_LOG_LINE_LENGTH = 300;

const int NORTH = 0;
const int NORTHEAST = 1;
const int EAST = 2;
const int SOUTHEAST = 3;
const int SOUTH = 4;
const int SOUTHWEST = 5;
const int WEST = 6;
const int NORTHWEST = 7;


const int WATER = '~';


const int TORCH1 = 256;
const int TORCH2 = 257;
const int TORCH3 = 258;
const int TORCH4 = 259;
const int TORCH5 = 260;
const int TORCH6 = 261;
const int TORCH7 = 262;

const int WATER1 = 263;
const int WATER2 = 264;
const int WATER3 = 265;
const int WATER4 = 266;
const int WATER5 = 267;
const int WATER6 = 268;
const int WATER7 = 269;
const int WATER8 = 270;
const int WATER9 = 271;
const int WATER10 = 272;
const int WATER11 = 273;

const int WOOD_FLOOR_1 = 274;

const int KOBOLD_1 = 275;
const int KOBOLD_2 = 276;
const int KOBOLD_3 = 277;

#endif