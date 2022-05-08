#include "headers\Tetromino.h"

void Tetromino::setTetromio(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->gameBoard = gameBoard;
	this->tileTexture.loadFromFile("resources/images/Tile.png");
	this->tetrominoTile.setTexture(&tileTexture);
	this->tetrominoTile.setSize({ INNER_CELL, INNER_CELL });
	this->setStartingPosition();
	this->ghostTexture.loadFromFile("resources/images/GhostTile.png");
	this->ghostTile.setTexture(&ghostTexture);
	this->ghostTile.setSize({ INNER_CELL, INNER_CELL });
	this->rotation = 0;
	this->updateGhost();
}

IShape::IShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { -1, 0 };
	this->tiles[1] = { 0, 0 };
	this->tiles[2] = { 1, 0 };
	this->tiles[3] = { 2, 0 };
	this->setTetromio(gameBoard);
	this->tetrominoTile.setFillColor(sf::Color(0, 255, 255)); //cyan
	this->ghostTile.setFillColor(sf::Color(0, 255, 255));
}

TShape::TShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { -1, 1 };
	this->tiles[2] = { 0, 0 };
	this->tiles[3] = { 1, 1 };
	this->setTetromio(gameBoard);
	this->tetrominoTile.setFillColor(sf::Color(255, 0, 255)); //pink
	this->ghostTile.setFillColor(sf::Color(255, 0, 255));
}

OShape::OShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { 1, 0 };
	this->tiles[2] = { 0, 0 };
	this->tiles[3] = { 1, 1 };
	this->setTetromio(gameBoard);
	this->tetrominoTile.setFillColor(sf::Color(255, 255, 40)); //yellow
	this->ghostTile.setFillColor(sf::Color(255, 255, 40));
}

LShape::LShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { -1, 1 };
	this->tiles[2] = { 1, 1 };
	this->tiles[3] = { 1, 0 };
	this->setTetromio(gameBoard);
	this->tetrominoTile.setFillColor(sf::Color(255, 170, 0)); //orange
	this->ghostTile.setFillColor(sf::Color(255, 170, 0));
}

JShape::JShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { -1, 1 };
	this->tiles[2] = { -1, 0 };
	this->tiles[3] = { 1, 1 };
	this->setTetromio(gameBoard);
	this->tetrominoTile.setFillColor(sf::Color(0, 70, 255)); //blue
	this->ghostTile.setFillColor(sf::Color(0, 70, 255));
}

SShape::SShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { -1, 0 };
	this->tiles[2] = { 0, 0 };
	this->tiles[3] = { 1, 1 };
	this->setTetromio(gameBoard);
	this->tetrominoTile.setFillColor(sf::Color(0, 255, 0)); //green
	this->ghostTile.setFillColor(sf::Color(0, 255, 0));
}

ZShape::ZShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard)
{
	this->tiles[0] = { 0, 1 };
	this->tiles[1] = { 0, 0 };
	this->tiles[2] = { -1, 1 };
	this->tiles[3] = { 1, 0 };
	this->setTetromio(gameBoard);
	this->tetrominoTile.setFillColor(sf::Color(255, 0, 0)); //red
	this->ghostTile.setFillColor(sf::Color(255, 0, 0));
}
