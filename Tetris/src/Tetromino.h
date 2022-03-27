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
	Tetromino(const TetrominoShape&, std::array<std::array<Cell, ROWS>, COLUMNS>*);
	Tetromino(const Tetromino&, std::array<std::array<Cell, ROWS>, COLUMNS>*);

	//Moves tetromino one line down. Retruns true if the move was valid.
	bool update();
	//Updates game matrix when tetromino gets to the end.
	void updateMatrix();
	//Resets tetromino shape and sets it to the starting position.
	void reset(const TetrominoShape&);

	//Moves tetromino left by one tile.
	void moveLeft();
	//Moves tetromino right by one tile.
	void moveRight();
	//Moves tetromino down, to the end of its way.
	void hardDrop();

	//Rotates tetromino between four states. Whether you press C or Z tetromino will rotate clockwise or not. Put true value to rotate clockwise. Retruns true if the roattion was legal.
	bool rotate(bool);
	//When the player attempts to rotate a tetromino, but the position it would normally occupy after basic rotation is obstructed, the game will attempt to "kick" the tetromino into an alternative position nearby.
	bool wallKick(unsigned char);
	bool updateMinosWallkick(const sf::Vector2i&);
	//Checks whether rotation was legel.
	bool legalRotation();

	//Returns tetromino's position.
	std::array<sf::Vector2i, 4> getPosition();
	//Retruns tetromino's color.
	sf::Color getColor();
	void setColor();
	//Retruns tetromino's shape.
	TetrominoShape getShape();
	int getRotation() { return this->rotation; }
};

class GhostTetromino : public Tetromino
{
public:
	GhostTetromino(Tetromino&);
	//Updates ghost based on current tetromino's position.
	void update(Tetromino&);
	//Updates ghost's shape on current tetromino.
	void reset(Tetromino&);
};

class NextTetromino : public Tetromino
{
	std::array < std::array < sf::RectangleShape, 22>, 24>* background;
public:
	NextTetromino(const TetrominoShape&, std::array < std::array < sf::RectangleShape, 22>, 24>*);
	void setPosition();
	void reset(const TetrominoShape&);
};