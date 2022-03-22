#include "SpawnTetromino.h"

TetrominoShape getShape(unsigned char x)
{
	return TetrominoShape(x);
}

std::array<sf::Vector2i, 4> spawnTetromino(const TetrominoShape& tShape)
{
	std::array<sf::Vector2i, 4> output_position;

	switch (tShape)
	{
	case TetrominoShape::I:
	{
		output_position[0] = { -1, 0 };
		output_position[1] = { 0, 0 };
		output_position[2] = { 1, 0 };
		output_position[3] = { 2, 0 };

		break;
	}
	case TetrominoShape::T:
	{
		output_position[0] = { 0, 1 };
		output_position[1] = { -1, 1 };
		output_position[2] = { 0, 0 };
		output_position[3] = { 1, 1 };

		break;
	}
	case TetrominoShape::O:
	{
		output_position[0] = { 0, 1 };
		output_position[1] = { 1, 0 };
		output_position[2] = { 0, 0 };
		output_position[3] = { 1, 1 };

		break;
	}
	case TetrominoShape::L:
	{
		output_position[0] = { 0, 1 };
		output_position[1] = { -1, 1 };
		output_position[2] = { 1, 1 };
		output_position[3] = { 1, 0 };

		break;
	}
	case TetrominoShape::J:
	{
		output_position[0] = { 0, 1 };
		output_position[1] = { -1, 1 };
		output_position[2] = { -1, 0 };
		output_position[3] = { 1, 1 };

		break;
	}
	case TetrominoShape::Z:
	{
		output_position[0] = { 0, 1 };
		output_position[1] = { 0, 0 };
		output_position[2] = { -1, 1 };
		output_position[3] = { 1, 0 };

		break;
	}
	case TetrominoShape::S:
	{
		output_position[0] = { 0, 1 };
		output_position[1] = { -1, 0 };
		output_position[2] = { 0, 0 };
		output_position[3] = { 1, 1 };
	}
	}

	return output_position;
}