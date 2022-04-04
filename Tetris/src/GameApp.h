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
#include "Animation.h"
#include "SoundManager.h"

class GameApp {

	sf::RenderWindow window;
	std::array<std::array<Cell, ROWS>, COLUMNS> matrix;
	std::array<std::array<sf::RectangleShape, 22>, 24> windowPosition;
	sf::Texture tileTexture;
	sf::Texture gameOverTexture;
	SoundManager sound;

	float dropTime = 0.9f;			void dropTimeReset();
	float moveTimeCooldown = 0.f;	void moveTimeCooldownReset() { this->moveTimeCooldown = 0.06f; }
	float hardDropCooldown = 0.f;	void hardDropCooldownReset() { this->hardDropCooldown = 0.5f; }
	float softDropCooldown = 0.f;	void softDropCooldownReset() { this->softDropCooldown = 0.05f; }
	float animationTime = 0.5f;		void animationTimeReset()	 { this->animationTime = 0.5f; }
	bool update = false;
	bool rotationAllowed = true;
	bool gameOverbool = false;
	bool inAnimation = false;

	int clearedLines = 0;
	int level = 0;
	int linesUntilTransition = 0;
	int score = 0;

public:
	GameApp(int statringLevel = 0);

	//Manages all tetromino movement based on user's input.
	void tetromnoMovement(Tetromino&);
	//Manages tetromino falling without user interaction. Updates tetromino if it falls to the end. Returns true if the tetromino hit the ground.
	bool fallingTetromino(Tetromino&, GhostTetromino&, NextTetromino&);
	//Searches game's matrix for full lines. Returns vector with lines number.
	std::vector<int> fullLines();
	//Clear full lines and updates the scoreboard.
	void clearLines(std::vector<int>& linesNumber, TextMenager&);
	//Displaying animation.
	void animationManager(std::vector<int>& linesNumber, float deltaTime, Animation&);
	//Drawes game board with tetromino which already fallen.
	void drawBoard();
	//Draws every tetromino.
	void drawTetromino(Tetromino&, GhostTetromino&, NextTetromino&);
	//Checks if new tetromino is able to spawn.
	bool gameOver(Tetromino&);
	//Ends game when gameOver returns true
	void endGame(sf::Sprite&);
	int run();

	void setUpSC();
	void transtionLevel();
	int scoreIncrease(unsigned char);
};