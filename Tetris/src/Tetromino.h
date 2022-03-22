#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "Cell.h"
#include "Global.h"
#include "SpawnTetromino.h"
#include "Color.h"

class Tetromino
{
protected:
	std::array<sf::Vector2i, 4> minos;
	TetrominoShape tShape;
	MinoColors color;
	unsigned char rotation;
public:
	std::array<std::array<Cell, ROWS>, COLUMNS>* matrix;

public:
	
	Tetromino() {};
	Tetromino(const TetrominoShape& tShape, std::array<std::array<Cell, ROWS>, COLUMNS>* matrix);
	Tetromino(const Tetromino& tetromio, std::array<std::array<Cell, ROWS>, COLUMNS>* matrix);

	bool update();
	void updateMatrix();
	void reset(const TetrominoShape& tShape);
	void moveLeft();
	void moveRight();
	void hardDrop();
	bool rotate(bool clockwise);
	bool wallKick(unsigned char previousRotation);
	bool updateMinosWallkick(const sf::Vector2i& v);
	bool legalRotation();

	std::array<sf::Vector2i, 4> getPosition();
	sf::Color getColor();
	void setColor();
	TetrominoShape getShape();
	int getRotation() { return this->rotation; }
};

class GhostTetromino : public Tetromino
{
public:
	GhostTetromino(Tetromino& tetromino);
	void update(Tetromino& tetromino);
	void reset(Tetromino& tetromino);
};

class NextTetromino : public Tetromino
{
	std::array < std::array < sf::RectangleShape, 22>, 24>* background;
public:
	NextTetromino(const TetrominoShape& tShape, std::array < std::array < sf::RectangleShape, 22>, 24>* background);
	void setPosition();
	void reset(const TetrominoShape& tShape);
};