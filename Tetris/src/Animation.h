#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "Global.h"
#include "Cell.h"

class Animation
{
	sf::Texture texture;
	std::array<sf::RectangleShape, ROWS> rows;
	float switchTime;

public:
	Animation() {};
	Animation(const std::array<std::array<Cell, ROWS>, COLUMNS>&);

	void display(sf::RenderWindow&, std::vector<int>& linesToDisplay);
};