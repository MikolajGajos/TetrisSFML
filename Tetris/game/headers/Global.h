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

enum class Volume
{
	menu, music, effects
};

class SoundVolume
{
	int music = 100;
	int effects = 100;
	int menu = 100;

public:
	static SoundVolume& getInstance()
	{
		static SoundVolume instance;
		return instance;
	}
	int getVolume(Volume vol)
	{
		switch (vol)
		{
		case Volume::menu:
			return this->menu;
		case Volume::music:
			return this->music;
		case Volume::effects:
			return this->effects;
		}
	}
	void changeVolume(Volume vol, int val)
	{
		switch (vol)
		{
		case Volume::menu:
			if((this->menu + val) >= 0 && (this->menu + val) <= 100)
				this->menu += val;
			break;
		case Volume::music:
			if ((this->music + val) >= 0 && (this->music + val) <= 100)
			this->music += val;
			break;
		case Volume::effects:
			if ((this->effects + val) >= 0 && (this->effects + val) <= 100)
			this->effects += val;
			break;
		}
	}
};
