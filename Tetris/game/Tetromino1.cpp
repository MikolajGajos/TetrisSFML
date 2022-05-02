#include "headers\Tetromino1.h"

bool Tetromino1::update()
{
	//checks if all minos can be moved down
	for (auto& tile : this->tiles)
	{
		if (tile.y + 1 == (*gameBoard)[0].size())
			return true;

		if ((*gameBoard)[tile.x][tile.y + 1].isFull() == true)
			return true;
	}

	for (auto& tile : this->tiles)
	{
		tile.y++;
	}
	return false;
}

void Tetromino1::updateMatrix()
{
	for (auto& tile : this->tiles)
	{
		(*gameBoard)[tile.x][tile.y].setFull(true);
		(*gameBoard)[tile.x][tile.y].setColor(cellShape.getFillColor());
	}
}

void Tetromino1::moveLeft()
{
	for (auto& tile : this->tiles)
	{
		if (tile.x - 1 < 0)
			return;
		if ((*gameBoard)[tile.x - 1][tile.y].isFull() == true)
			return;
	}
	for (auto& mino : this->tiles)
	{
		mino.x -= 1;
	}
}

void Tetromino1::moveRight()
{
	for (auto& tile : this->tiles)
	{
		if (tile.x + 1 > (*gameBoard).size() - 1)
			return;
		if ((*gameBoard)[tile.x + 1][tile.y].isFull() == true)
			return;
	}
	for (auto& mino : this->tiles)
	{
		mino.x += 1;
	}
}

void Tetromino1::hardDrop()
{
	while (!update()) {}
}

void Tetromino1::setStartingPosition()
{
	for (auto& tile : tiles)
	{
		tile.x += SPAWN_POINT.x;
		tile.y += SPAWN_POINT.y;
	}
}

Tetromino1* Tetromino1::getNew(int num, std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	switch (TetrominoShape1(num))
	{
	case TetrominoShape1::I:
		return new IShape(gameBoard);

	case TetrominoShape1::T:
		return new TShape(gameBoard);

	case TetrominoShape1::O:
		return new OShape(gameBoard);

	case TetrominoShape1::L:
		return new LShape(gameBoard);

	case TetrominoShape1::J:
		return new JShape(gameBoard);

	case TetrominoShape1::S:
		return new SShape(gameBoard);

	case TetrominoShape1::Z:
		return new ZShape(gameBoard);

	}
}

void Tetromino1::display(sf::RenderWindow& window)
{
	for (auto& tile : tiles)
	{
		if (tile.y >= 2)
		{
			cellShape.setPosition(CELL_SIZE * tile.x + (*gameBoard)[0][0].getPosition().x, tile.y * CELL_SIZE + (*gameBoard)[0][0].getPosition().y);
			window.draw(cellShape);
		}
	}
}

