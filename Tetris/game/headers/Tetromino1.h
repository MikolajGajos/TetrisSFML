#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "Cell.h"
#include "Global.h"

enum class TetrominoShape1
{
	I, T, O, L, J, S, Z
};

class Tetromino1
{
protected:
	std::array<sf::Vector2i, 4> tiles;
	sf::RectangleShape tetrominoTile;
	sf::Texture tileTexture;
	std::array<sf::Vector2i, 4> ghostTiles;
	sf::RectangleShape ghostTile;
	sf::Texture ghostTexture;
	unsigned char rotation;
	std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard;

protected:
	void setTetromio(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
	void setStartingPosition();
	bool legalRotation();
	virtual bool wallKick(unsigned char);
	bool legalKick(const sf::Vector2i&);
	void displayGhost(sf::RenderWindow& window);

public:
	void updateGhost();
	//Moves tetromino one line down. Retruns true if the move was valid.
	bool update();
	//Updates game matrix when tetromino gets to the end.
	void updateMatrix();

	//Moves tetromino left by one tile.
	void moveLeft();
	//Moves tetromino right by one tile.
	void moveRight();
	//Moves tetromino down, to the end of its way.
	void hardDrop();
	//Rotates tetromino between four states. Put true value to rotate clockwise.
	virtual void rotate(bool);

	Tetromino1* getNew(int, std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
	void display(sf::RenderWindow& window);
};

class IShape : public Tetromino1
{
	bool wallKick(unsigned char);
public:
	IShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
	void rotate(bool);
};

class TShape : public Tetromino1
{
public:
	TShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};

class OShape : public Tetromino1
{
public:
	OShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
	void rotate(bool) { return; }
};

class LShape : public Tetromino1
{
public:
	LShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};

class JShape : public Tetromino1
{
public:
	JShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};

class ZShape : public Tetromino1
{
public:
	ZShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};

class SShape : public Tetromino1
{
public:
	SShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};