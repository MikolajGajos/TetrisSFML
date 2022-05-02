#include "headers\Tetromino1.h"

void Tetromino1::setTetromio(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->gameBoard = gameBoard;
	this->texture.loadFromFile("resources/images/Tile.png");
	this->cellShape.setTexture(&texture);
	this->cellShape.setSize({ INNER_CELL, INNER_CELL });
	this->setStartingPosition();
	this->rotation = 0;
}

IShape::IShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { -1, 0 };
	this->tiles[1] = { 0, 0 };
	this->tiles[2] = { 1, 0 };
	this->tiles[3] = { 2, 0 };
	this->setTetromio(gameBoard);
	this->cellShape.setFillColor(sf::Color(0, 255, 255)); //cyan
}

TShape::TShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { -1, 1 };
	this->tiles[2] = { 0, 0 };
	this->tiles[3] = { 1, 1 };
	this->setTetromio(gameBoard);
	this->cellShape.setFillColor(sf::Color(255, 0, 255)); //pink
}

OShape::OShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { 1, 0 };
	this->tiles[2] = { 0, 0 };
	this->tiles[3] = { 1, 1 };
	this->setTetromio(gameBoard);
	this->cellShape.setFillColor(sf::Color(255, 255, 0)); //yellow
}

LShape::LShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { -1, 1 };
	this->tiles[2] = { 1, 1 };
	this->tiles[3] = { 1, 0 };
	this->setTetromio(gameBoard);
	this->cellShape.setFillColor(sf::Color(255, 170, 0)); //orange
}

JShape::JShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { -1, 1 };
	this->tiles[2] = { -1, 0 };
	this->tiles[3] = { 1, 1 };
	this->setTetromio(gameBoard);
	this->cellShape.setFillColor(sf::Color(39, 39, 160)); //blue
}

SShape::SShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { -1, 0 };
	this->tiles[2] = { 0, 0 };
	this->tiles[3] = { 1, 1 };
	this->setTetromio(gameBoard);
	this->cellShape.setFillColor(sf::Color(0, 255, 0)); //green
}

ZShape::ZShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { 0, 0 };
	this->tiles[2] = { -1, 1 };
	this->tiles[3] = { 1, 0 };
	this->setTetromio(gameBoard);
	this->cellShape.setFillColor(sf::Color(255, 0, 0)); //red
}
