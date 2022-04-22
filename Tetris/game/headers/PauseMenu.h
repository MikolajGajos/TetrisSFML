#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

enum class PauseOutput
{
	noPause, resume, exit
};

class PauseMenu
{
	sf::RenderWindow* window;
	bool inPause = false;
	bool check = true;
	int* score;
	int* level;
	int* lines;
	sf::Font font;
	sf::Text scoreText;
	sf::Text levelText;
	sf::Text linesText;
	sf::Texture texture;
	sf::Sprite backGround;

	Button resume;
	Button exit;
	ButtonManager buttons;
	bool changeAllowed = true;
	bool escapeAllowed = false;

private:
	void setText();
	void updateText();
	bool checkForEnd();
	void manageButtons();
	PauseOutput getPressedButton();
	PauseOutput pause();
	void displayText();
	void display();

public:
	PauseMenu(sf::RenderWindow*, int* score, int* level, int* lines);

	PauseOutput checkForPause();
};
