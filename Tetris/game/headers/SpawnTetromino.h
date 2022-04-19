#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "Global.h"

enum class TetrominoShape
{
	I, T, O, L, J, S, Z
};

enum class TetrominoColor
{
	red, cyan, yellow, pink, blue, green, orange
};

//Gives tetromino a shape based on the the number. The tetromino's shape is defined by the enum class.
TetrominoShape getShape(unsigned char x);

std::array<sf::Vector2i, 4> spawnTetromino(const TetrominoShape& tShape);