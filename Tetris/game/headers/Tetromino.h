#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "Cell.h"
#include "Global.h"

enum class TetrominoShape1
{
	I, T, O, L, J, S, Z
};

class Tetromino
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
	//Updates ghost based on tetromino position.
	void updateGhost();
	//Moves tetromino one line down. Retruns true if the move was valid.
	bool update();
	//Updates game matrix when tetromino gets to the end.
	void updateMatrix();

	//Moves tetromino left.
	void moveLeft();
	//Moves tetromino right.
	void moveRight();
	//Moves tetromino all the way to the end.
	void hardDrop();
	//Rotates tetromino between four states. Put true value to rotate clockwise.
	virtual void rotate(bool);

	Tetromino* getNew(int, std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
	void display(sf::RenderWindow& window);
	virtual void displayAsNext(sf::RenderWindow& window);
};

class IShape : public Tetromino
{
	bool wallKick(unsigned char);
public:
	IShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
	void rotate(bool);
	void displayAsNext(sf::RenderWindow& window);
};

class TShape : public Tetromino
{
public:
	TShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};

class OShape : public Tetromino
{
public:
	OShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
	void rotate(bool) { return; }
	void displayAsNext(sf::RenderWindow& window);
};

class LShape : public Tetromino
{
public:
	LShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};

class JShape : public Tetromino
{
public:
	JShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};

class ZShape : public Tetromino
{
public:
	ZShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};

class SShape : public Tetromino
{
public:
	SShape(std::array<std::array<Cell, ROWS + 2>, COLUMNS>*);
};

