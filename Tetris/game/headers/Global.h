#pragma once

const unsigned char INNER_CELL = 36;

const unsigned char CELL_BORDER = 2;

const unsigned char CELL_SIZE = INNER_CELL + CELL_BORDER;

const unsigned char COLUMNS = 10;

const unsigned char ROWS = 20;

const unsigned char MATRIX_POS_X = 1;
const unsigned char MATRIX_POS_Y = 1;

const int WINDOW_SIZE_X = 2 * CELL_SIZE * (COLUMNS + 2);
const int WINDOW_SIZE_Y = CELL_SIZE * (ROWS + 2);

const sf::Vector2f SPAWN_POINT = { COLUMNS / 2 - 1, 0 };

class DeltaTime
{
	sf::Clock clock;
	float dt;
	DeltaTime() { dt = 0.f; };

public:
	static DeltaTime& getInstance()
	{
		static DeltaTime instance;
		return instance;
	}

	float getDT() { return dt; }
	void update() { this->dt = clock.restart().asSeconds(); }
};