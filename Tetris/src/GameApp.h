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
	float moveTimeCooldown = 0.f;	void moveTimeCooldownReset()	{ this->moveTimeCooldown = 0.06f; }
	float hardDropCooldown = 0.f;	void hardDropCooldownReset()	{ this->hardDropCooldown = 0.5f; }
	float softDropCooldown = 0.f;	void softDropCooldownReset()	{ this->softDropCooldown = 0.1f; }
	bool update = false;
	bool rotationAllowed = true;		
	bool movementAllowed = true;

	int clearedLines = 0;
	int level = 1;
	int linesUntilTransition = 0;
	int score = 0;
	bool gameOverbool = false;

public:
	GameApp(int statringLevel = 0);

	//Manages all tetromino movement based on user's input.
	void tetromnoMovement(Tetromino&, sf::Event&);
	//Manages tetromino falling without user interaction. Updates tetromino if it falls to the end.
	void fallingTetromino(Tetromino&, GhostTetromino&, NextTetromino&);
	//Searches game's matrix and cleares full lines. If the line was cleared it adds points to the game score.
	void fullLines();
	//Draws background.
	void drawBackGround(BackgroundManager);
	//Drawes game board with tetromino which already fallen.
	void drawBoard();
	//Draws currently falling tetromino and its ghost.
	void drawTetromino(Tetromino&, GhostTetromino&);
	//Draws next tetromino.
	void drawNextTetromino(NextTetromino&);
	//Checks if new tetromino is able to spawn.
	bool gameOver(Tetromino&);
	//Ends game when gameOver returns true
	void endGame();
	int run();

	void setUpSC();
	void transtionLevel();
	int scoreIncrease(unsigned char);
};