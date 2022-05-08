#pragma once
#include <iostream>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include <random>
#include <chrono>

#include "Global.h"
#include "Tetromino.h"
#include "Cell.h"
#include "TextAndBackground.h"
#include "Animation.h"
#include "GameSounds.h"
#include "PauseMenu.h"

class GameApp {

	sf::RenderWindow* window;
	std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard = new std::array<std::array<Cell, ROWS + 2>, COLUMNS>;
	std::array<std::array<sf::RectangleShape, 22>, 24>* windowPosition = new std::array<std::array<sf::RectangleShape, 22>, 24>;
	
	//game objects
	GameBackground background;
	PauseMenu* pause;
	GameText gameText;
	GameSound gameSound;
	Animation* gameAnimation;
	Tetromino* tetromino;
	Tetromino* nextTetromino;

	float dropTime = 0.9f;			void dropTimeReset();
	float moveTimeCooldown = 0.f;	void moveTimeCooldownReset() { this->moveTimeCooldown = 0.06f; }
	float hardDropCooldown = 0.f;	void hardDropCooldownReset() { this->hardDropCooldown = 0.5f; }
	float softDropCooldown = 0.f;	void softDropCooldownReset() { this->softDropCooldown = 0.05f; }
	float animationTime = 0.5f;		void animationTimeReset()	 { this->animationTime = 0.5f; }
	bool pauseAllowed = true;
	bool update = false;
	bool rotationAllowed = true;
	bool gameOverbool = false;

	int clearedLines = 0;
	int level = 0;
	int linesUntilTransition = 0;
	int score = 0;

	PauseOutput pauseManagement();
	//Waits for a given time and displays the timer.
	void wait(float time);
	//Manages all tetromino movement based on user's input.
	void tetromnoMovement();
	//Manages tetromino falling without user interaction. Updates tetromino if it falls to the end. Returns true if the tetromino hit the ground.
	bool fallingTetromino();
	//Searches game's matrix for full lines.
	void fullLines();
	//Clear full lines and updates the scoreboard.
	void clearLines(std::vector<int>& linesNumber);
	//Drawes game board with tetromino which already fallen.
	void drawBoard();
	//Draws every tetromino.
	void drawTetromino();
	//Checks if new tetromino is able to spawn.
	bool gameOver();
	//Draws game ending screen.
	bool endGame();

	bool updateGame();
	void drawGame();
	void manageTimers();
	void setUpSC();
	void transtionLevel();
	int scoreIncrease(unsigned char);
public:
	GameApp(sf::RenderWindow*);
	~GameApp();	
	int run();
	void setStartingLevel(unsigned char lvl) { this->level = lvl; }
};