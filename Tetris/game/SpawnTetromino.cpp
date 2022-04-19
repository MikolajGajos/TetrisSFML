#include "headers/SpawnTetromino.h"

TetrominoShape getShape(unsigned char x)
{
	return TetrominoShape(x);
}

std::array<sf::Vector2i, 4> spawnTetromino(const TetrominoShape& tShape)
{
	std::array<sf::Vector2i, 4> position;

	switch (tShape)
	{
	case TetrominoShape::I:
	{
		position[0] = { -1, 0 };
		position[1] = { 0, 0 };
		position[2] = { 1, 0 };
		position[3] = { 2, 0 };

		break;
	}
	case TetrominoShape::T:
	{
		position[0] = { 0, 1 };
		position[1] = { -1, 1 };
		position[2] = { 0, 0 };
		position[3] = { 1, 1 };

		break;
	}
	case TetrominoShape::O:
	{
		position[0] = { 0, 1 };
		position[1] = { 1, 0 };
		position[2] = { 0, 0 };
		position[3] = { 1, 1 };

		break;
	}
	case TetrominoShape::L:
	{
		position[0] = { 0, 1 };
		position[1] = { -1, 1 };
		position[2] = { 1, 1 };
		position[3] = { 1, 0 };

		break;
	}
	case TetrominoShape::J:
	{
		position[0] = { 0, 1 };
		position[1] = { -1, 1 };
		position[2] = { -1, 0 };
		position[3] = { 1, 1 };

		break;
	}
	case TetrominoShape::Z:
	{
		position[0] = { 0, 1 };
		position[1] = { 0, 0 };
		position[2] = { -1, 1 };
		position[3] = { 1, 0 };

		break;
	}
	case TetrominoShape::S:
	{
		position[0] = { 0, 1 };
		position[1] = { -1, 0 };
		position[2] = { 0, 0 };
		position[3] = { 1, 1 };
	}
	}
	return position;
}