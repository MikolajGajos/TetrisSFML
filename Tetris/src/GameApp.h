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
	std::array<std::array<sf::RectangleShape, 22>, 24> background;
	sf::Texture tileTexture;
	sf::Texture ghostTexture;
	sf::Texture backgroundTexture;
	sf::Texture borderTexture;

	float dropTime = 0.9f;			void dropTimeReset()			{ this->dropTime = 0.9f; }
	float moveTimeCooldown = 0.f;	void moveTimeCooldownReset()	{ this->moveTimeCooldown = 0.12f; }
	float hardDropCooldown = 0.f;	void hardDropCooldownReset()	{ this->hardDropCooldown = 0.5f; }
	float softDropCooldown = 0.f;	void softDropCooldownReset()	{ this->softDropCooldown = 0.1f; }
	float timeUntilReset = 0.f;;	void timeUntilResetReset()		{ this->timeUntilReset = 0.5f; }
	bool update = false;
	bool rotationAllowed = true;		

	int clearedLines = 0;

public:
	GameApp();

	void tetromnoMovement(Tetromino& tetromino, sf::Event& event);
	void fallingTetromino(Tetromino& tetromino, GhostTetromino& ghostTetromino, NextTetromino& nextTetromino);
	int fullLines();
	void drawBackGround();
	void drawBoard();
	void drawTetromino(Tetromino& tetromino, GhostTetromino& ghostTetromino);
	void drawNextTetromino(NextTetromino& nextTetromino);
	bool gameOver();
	void run();
};