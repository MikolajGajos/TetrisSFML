#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "Global.h"

enum class TetrominoShape
{
	I, T, O, L, J, S, Z
};

TetrominoShape getShape(unsigned char x);

std::array<sf::Vector2i, 4> spawnTetromino(const TetrominoShape& tShape);