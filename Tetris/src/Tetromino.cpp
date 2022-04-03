#include "Tetromino.h"
#include <iostream>

void setStatringPosition(std::array<sf::Vector2i, 4>& tiles)
{
	for (auto& tile : tiles)
	{
		tile.x += SPAWN_POINT.x;
		tile.y += SPAWN_POINT.y;
	}
}

Tetromino::Tetromino(const TetrominoShape& tShape, std::array<std::array<Cell, ROWS>, COLUMNS>* matrix)
{
	this->tShape = tShape;
	this->tiles = spawnTetromino(tShape);
	setStatringPosition(this->tiles);
	this->rotation = 0;
	this->setColor();	
	this->matrix = matrix;
	this->texture.loadFromFile("src/rsrc/Tile.png");
	this->cellShape.setSize({ CELL_SIZE, CELL_SIZE });
	this->cellShape.setFillColor(this->getColor());
	this->cellShape.setTexture(&texture);
}

Tetromino::Tetromino(const Tetromino& tetromio, std::array<std::array<Cell, ROWS>, COLUMNS>* matrix)
{
	this->tShape = tetromio.tShape;
	this->tiles = tetromio.tiles;
	this->rotation = tetromio.rotation;
	this->matrix = matrix;
	this->texture.loadFromFile("src/rsrc/Tile.png");
	this->cellShape.setSize({ CELL_SIZE, CELL_SIZE });
	this->cellShape.setFillColor(this->getColor());
	this->cellShape.setTexture(&texture);
}

bool Tetromino::update()
{
	//checks if all minos can be moved down
	for (auto& tile : this->tiles)
	{
		if (tile.y + 1 == ROWS)
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
	while (true)
	{
		for (auto& tile : this->tiles)
		{
			if (tile.y + 1 == ROWS)
				return;

			if ((*matrix)[tile.x][tile.y + 1].isFull() == true)
				return;
		}
		for (auto& tile : this->tiles)
		{
			tile.y++;
		}
	}
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
		this->color = MinoColors::cyan;
		break;
	case TetrominoShape::T:
		this->color = MinoColors::pink;
		break;
	case TetrominoShape::O:
		this->color = MinoColors::yellow;
		break;
	case TetrominoShape::L:
		this->color = MinoColors::orange;
		break;
	case TetrominoShape::J:
		this->color = MinoColors::blue;
		break;
	case TetrominoShape::S:
		this->color = MinoColors::red;
		break;
	case TetrominoShape::Z:
		this->color = MinoColors::green;
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
		cellShape.setPosition(CELL * tile.x + (*matrix)[0][0].getPosition().x, tile.y * CELL + (*matrix)[0][0].getPosition().y);
		window.draw(cellShape);
	}
}

sf::Color Tetromino::getColor()
{
	sf::Color color;

	switch (this->color)
	{
	case MinoColors::red:
		color = { 255,0,0,255 };
		break;
	case MinoColors::orange:
		color = { 255,170,0,255 };
		break;
	case MinoColors::cyan:
		color = { 0,255,255,255 };
		break;
	case MinoColors::yellow:
		color = { 255,255,0,255 };
		break;
	case MinoColors::pink:
		color = { 255,0,255,255 };
		break;
	case MinoColors::blue:
		color = { 39,39,160,255 };
		break;
	case MinoColors::green:
		color = { 0,255,0,255 };
		break;
	case MinoColors::ghostColor:
		color = { 37,37,45,255 };
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
	this->texture.loadFromFile("src/rsrc/GhostTile.png");
	this->cellShape.setSize({ CELL_SIZE, CELL_SIZE });
	this->cellShape.setFillColor(this->getColor());
	this->cellShape.setTexture(&texture);
}

void GhostTetromino::update(Tetromino& tetromino)
{
	this->tiles = tetromino.getPosition();

	while (true)
	{
		for (auto& tile : this->tiles)
		{
			if (tile.y + 1 == ROWS)
				return;

			if ((*matrix)[tile.x][tile.y + 1].isFull() == true)
				return;
		}
		for (auto& mino : this->tiles)
		{
			mino.y++;
		}
	}
}

void GhostTetromino::reset(Tetromino& tetromino)
{
	this->tShape = tetromino.getShape();
	this->tiles = spawnTetromino(this->tShape);
	this->update(tetromino);
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
	this->texture.loadFromFile("src/rsrc/Tile.png");
	this->cellShape.setSize({ CELL_SIZE, CELL_SIZE });
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
			cellShape.setPosition(tile.x * (CELL), tile.y * CELL);
			window.draw(cellShape);
		}
	}
	else if (tShape == TetrominoShape::I)
	{
		for (auto& tile : tiles)
		{
			cellShape.setPosition(tile.x * (CELL), (tile.y + 0.5) * CELL);
			window.draw(cellShape);
		}
	}
	else
	{
		for (auto& tile : tiles)
		{
			cellShape.setPosition((tile.x + 0.5f) * CELL, tile.y * CELL);
			window.draw(cellShape);
		}
	}
}
