#pragma once

const unsigned char CELL_SIZE = 36;

const unsigned char CELL_SPCACE = 2;

const unsigned char CELL = CELL_SIZE + CELL_SPCACE;

const unsigned char COLUMNS = 10;

const unsigned char ROWS = 20;

const int WINDOW_SIZE_X = 2 * CELL * (COLUMNS + 2);
const int WINDOW_SIZE_Y = CELL * (ROWS + 2);

const sf::Vector2f SPAWN_POINT = { COLUMNS / 2 - 1, 0 };