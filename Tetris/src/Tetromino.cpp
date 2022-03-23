#include "Tetromino.h"
#include <iostream>

void setStatringPosition(std::array<sf::Vector2i, 4>& minos)
{
	for (auto& mino : minos)
	{
		mino.x += SPAWN_POINT.x;
		mino.y += SPAWN_POINT.y;
	}
}

Tetromino::Tetromino(const TetrominoShape& tShape, std::array<std::array<Cell, ROWS>, COLUMNS>* matrix)
{
	this->tShape = tShape;
	this->minos = spawnTetromino(tShape);
	setStatringPosition(this->minos);
	this->rotation = 0;
	this->setColor();	
	this->matrix = matrix;
	
}

Tetromino::Tetromino(const Tetromino& tetromio, std::array<std::array<Cell, ROWS>, COLUMNS>* matrix)
{
	this->tShape = tetromio.tShape;
	this->minos = tetromio.minos;
	this->rotation = tetromio.rotation;
	this->matrix = matrix;
}

bool Tetromino::update()
{
	for (auto& mino : this->minos)
	{
		if (mino.y + 1 == ROWS)
			return 1;

		if ((*matrix)[mino.x][mino.y + 1].isFull() == true)
			return 1;
	}

	for (auto& mino : this->minos)
	{
		mino.y++;
	}
	return 0;
}

void Tetromino::updateMatrix()
{
	for (auto& mino : this->minos)
	{
		(*matrix)[mino.x][mino.y].setFull(true);
		(*matrix)[mino.x][mino.y].setColor(this->getColor());
	}
}

void Tetromino::reset(const TetrominoShape& tShape)
{
	this->tShape = tShape;
	this->minos = spawnTetromino(tShape);
	setStatringPosition(this->minos);
	this->rotation = 0;
	this->setColor();
}

void Tetromino::moveLeft()
{
	for (auto& mino : this->minos)
	{
		if (mino.x - 1 < 0)
			return;
		if ((*matrix)[mino.x - 1][mino.y].isFull() == true)
			return;
	}
	for (auto& mino : this->minos)
	{
		mino.x -= 1;
	}
}

void Tetromino::moveRight()
{
	for (auto& mino : this->minos)
	{
		if (mino.x + 1 > (*matrix).size() - 1)
			return;
		if ((*matrix)[mino.x + 1][mino.y].isFull() == true)
			return;
	}
	for (auto& mino : this->minos)
	{
		mino.x += 1;
	}
}

void Tetromino::hardDrop()
{
	while (true)
	{
		for (auto& mino : this->minos)
		{
			if (mino.y + 1 == ROWS)
				return;

			if ((*matrix)[mino.x][mino.y + 1].isFull() == true)
				return;
		}
		for (auto& mino : this->minos)
		{
			mino.y++;
		}
	}
}

std::array<sf::Vector2i, 4> Tetromino::getPosition()
{
	return this->minos;
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
	this->color = MinoColors::ghostColor;
	this->minos = spawnTetromino(this->tShape);
	this->matrix = tetromino.matrix;
}

void GhostTetromino::update(Tetromino& tetromino)
{
	this->minos = tetromino.getPosition();

	while (true)
	{
		for (auto& mino : this->minos)
		{
			if (mino.y + 1 == ROWS)
				return;

			if ((*matrix)[mino.x][mino.y + 1].isFull() == true)
				return;
		}
		for (auto& mino : this->minos)
		{
			mino.y++;
		}
	}
}

void GhostTetromino::reset(Tetromino& tetromino)
{
	this->tShape = tetromino.getShape();
	this->color = MinoColors::ghostColor;
	this->minos = spawnTetromino(this->tShape);
	this->update(tetromino);
}

/// ///////////////////////////////////////////////////////////////////////////////////////////////////

NextTetromino::NextTetromino(const TetrominoShape& tShape, std::array < std::array < sf::RectangleShape, 22>, 24>* background)
{
	this->background = background;
	this->rotation = 0;
	this->tShape = tShape;
	this->setColor();
	this->minos = spawnTetromino(tShape);
	this->setPosition();
}

void NextTetromino::setPosition()
{
	for (auto& mino : this->minos)
	{
		mino.x += 15;
		mino.y += 8;
	}
}

void NextTetromino::reset(const TetrominoShape& tShape)
{
	this->minos = spawnTetromino(tShape);
	this->setPosition();
	this->rotation = 0;
	this->tShape = tShape;
	this->setColor();
}
