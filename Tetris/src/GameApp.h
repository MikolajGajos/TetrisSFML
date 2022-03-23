#pragma once
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

#include <random>
#include <chrono>

#include "Global.h"
#include "Tetromino.h"
#include "Color.h"
#include "Cell.h"
#include "TextManager.h"

class GameApp {

	sf::RenderWindow window;
	std::array<std::array<Cell, ROWS>, COLUMNS> matrix;
	std::array<std::array<sf::RectangleShape, 22>, 24> windowPosition;
	sf::Texture tileTexture;
	sf::Texture ghostTexture;
	sf::Texture gameBackgroundTexture;

	float dropTime = 0.9f;			void dropTimeReset();
	float moveTimeCooldown = 0.f;	void moveTimeCooldownReset()	{ this->moveTimeCooldown = 0.045f; }
	float hardDropCooldown = 0.f;	void hardDropCooldownReset()	{ this->hardDropCooldown = 0.5f; }
	float softDropCooldown = 0.f;	void softDropCooldownReset()	{ this->softDropCooldown = 0.1f; }
	bool update = false;
	bool rotationAllowed = true;		
	bool movementAllowed = true;

	int clearedLines = 0;
	int level = 1;
	int linesUntilTransition = 0;
	int score = 0;

public:
	GameApp(int statringLevel = 0);

	void tetromnoMovement(Tetromino& tetromino, sf::Event& event);
	void fallingTetromino(Tetromino& tetromino, GhostTetromino& ghostTetromino, NextTetromino& nextTetromino);
	void fullLines();
	void drawBackGround();
	void drawBoard();
	void drawTetromino(Tetromino& tetromino, GhostTetromino& ghostTetromino);
	void drawNextTetromino(NextTetromino& nextTetromino);
	bool gameOver();
	int run();

	void setUpSC();
	void transtionLevel();
	int scoreIncrease(unsigned char lines);
};