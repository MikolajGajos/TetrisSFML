#include "headers/Tetromino.h"
#include <iostream>

void setStatringPosition(std::array<sf::Vector2i, 4>& tiles)
{
	for (auto& tile : tiles)
	{
		tile.x += SPAWN_POINT.x;
		tile.y += SPAWN_POINT.y;
	}
}

Tetromino::Tetromino(const TetrominoShape& tShape, std::array<std::array<Cell, ROWS + 2>, COLUMNS>* matrix)
{
	this->tShape = tShape;
	this->tiles = spawnTetromino(tShape);
	setStatringPosition(this->tiles);
	this->rotation = 0;
	this->setColor();
	this->cellShape.setFillColor(this->getColor());

	this->matrix = matrix;
	this->texture.loadFromFile("resources/images/Tile.png");
	this->cellShape.setTexture(&texture);
	this->cellShape.setSize({ INNER_CELL, INNER_CELL });
}

bool Tetromino::update()
{
	//checks if all minos can be moved down
	for (auto& tile : this->tiles)
	{
		if (tile.y + 1 == (*matrix)[0].size())
			return true;

		if ((*matrix)[tile.x][tile.y + 1].isFull() == true)
			return true;
	}

	for (auto& tile : this->tiles)
	{
		tile.y++;
	}
	return false;
}

void Tetromino::updateMatrix()
{
	for (auto& tile : this->tiles)
	{
		(*matrix)[tile.x][tile.y].setFull(true);
		(*matrix)[tile.x][tile.y].setColor(this->getColor());
	}
}

void Tetromino::reset(const TetrominoShape& tShape)
{
	this->tShape = tShape;
	this->tiles = spawnTetromino(tShape);
	setStatringPosition(this->tiles);
	this->rotation = 0;
	this->setColor();
	this->cellShape.setFillColor(this->getColor());
}

void Tetromino::moveLeft()
{
	for (auto& tile : this->tiles)
	{
		if (tile.x - 1 < 0)
			return;
		if ((*matrix)[tile.x - 1][tile.y].isFull() == true)
			return;
	}
	for (auto& mino : this->tiles)
	{
		mino.x -= 1;
	}
}

void Tetromino::moveRight()
{
	for (auto& tile : this->tiles)
	{
		if (tile.x + 1 > (*matrix).size() - 1)
			return;
		if ((*matrix)[tile.x + 1][tile.y].isFull() == true)
			return;
	}
	for (auto& mino : this->tiles)
	{
		mino.x += 1;
	}
}

void Tetromino::hardDrop()
{
	while (!update()) {}
}

std::array<sf::Vector2i, 4> Tetromino::getPosition()
{
	return this->tiles;
}

void Tetromino::setColor()
{
	switch (this->tShape)
	{
	case TetrominoShape::I:
		this->color = TetrominoColor::cyan;
		break;
	case TetrominoShape::T:
		this->color = TetrominoColor::pink;
		break;
	case TetrominoShape::O:
		this->color = TetrominoColor::yellow;
		break;
	case TetrominoShape::L:
		this->color = TetrominoColor::orange;
		break;
	case TetrominoShape::J:
		this->color = TetrominoColor::blue;
		break;
	case TetrominoShape::S:
		this->color = TetrominoColor::red;
		break;
	case TetrominoShape::Z:
		this->color = TetrominoColor::green;
		break;
	default:
		break;
	}
}

TetrominoShape Tetromino::getShape()
{
	return this->tShape;
}

void Tetromino::display(sf::RenderWindow& window)
{
	for (auto& tile : tiles)
	{
		if (tile.y >= 2)
		{
			cellShape.setPosition(CELL_SIZE * tile.x + (*matrix)[0][0].getPosition().x, tile.y * CELL_SIZE + (*matrix)[0][0].getPosition().y);
			window.draw(cellShape);
		}		
	}
}

sf::Color Tetromino::getColor()
{
	sf::Color color;

	switch (this->color)
	{
	case TetrominoColor::red:
		color = { 255,0,0,255 };
		break;
	case TetrominoColor::orange:
		color = { 255,170,0,255 };
		break;
	case TetrominoColor::cyan:
		color = { 0,255,255,255 };
		break;
	case TetrominoColor::yellow:
		color = { 255,255,0,255 };
		break;
	case TetrominoColor::pink:
		color = { 255,0,255,255 };
		break;
	case TetrominoColor::blue:
		color = { 39,39,160,255 };
		break;
	case TetrominoColor::green:
		color = { 0,255,0,255 };
		break;
	}

	return color;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

GhostTetromino::GhostTetromino(Tetromino& tetromino)
{
	this->tShape = tetromino.getShape();
	this->setColor();
	this->tiles = spawnTetromino(this->tShape);
	this->matrix = tetromino.matrix;
	this->texture.loadFromFile("resources/images/GhostTile.png");
	this->cellShape.setSize({ INNER_CELL, INNER_CELL });
	this->cellShape.setFillColor(this->getColor());
	this->cellShape.setTexture(&texture);
}

void GhostTetromino::updateGhost(Tetromino& tetromino)
{
	this->tiles = tetromino.getPosition();
	while (!update()) {}
}

void GhostTetromino::reset(Tetromino& tetromino)
{
	this->tShape = tetromino.getShape();
	this->tiles = spawnTetromino(this->tShape);
	this->updateGhost(tetromino);
	this->setColor();
	this->cellShape.setFillColor(this->getColor());
}

/// ///////////////////////////////////////////////////////////////////////////////////////////////////

NextTetromino::NextTetromino(const TetrominoShape& tShape, std::array < std::array < sf::RectangleShape, 22>, 24>* background)
{
	this->background = background;
	this->rotation = 0;
	this->tShape = tShape;
	this->setColor();
	this->tiles = spawnTetromino(tShape);
	this->setPosition();
	this->texture.loadFromFile("resources/images/Tile.png");
	this->cellShape.setSize({ INNER_CELL, INNER_CELL });
	this->cellShape.setFillColor(this->getColor());
	this->cellShape.setTexture(&texture);
}

void NextTetromino::setPosition()
{
	for (auto& tile : this->tiles)
	{
		tile.x += 15;
		tile.y += 8;
	}
}

void NextTetromino::reset(const TetrominoShape& tShape)
{
	this->tiles = spawnTetromino(tShape);
	this->setPosition();
	this->rotation = 0;
	this->tShape = tShape;
	this->setColor();
	this->cellShape.setFillColor(this->getColor());
}

void NextTetromino::display(sf::RenderWindow& window)
{
	if (tShape == TetrominoShape::O)
	{
		for (auto& tile : tiles)
		{
			cellShape.setPosition(tile.x * (CELL_SIZE), tile.y * CELL_SIZE);
			window.draw(cellShape);
		}
	}
	else if (tShape == TetrominoShape::I)
	{
		for (auto& tile : tiles)
		{
			cellShape.setPosition(tile.x * (CELL_SIZE), (tile.y + 0.5) * CELL_SIZE);
			window.draw(cellShape);
		}
	}
	else
	{
		for (auto& tile : tiles)
		{
			cellShape.setPosition((tile.x + 0.5f) * CELL_SIZE, tile.y * CELL_SIZE);
			window.draw(cellShape);
		}
	}
}
