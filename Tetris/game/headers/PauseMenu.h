#pragma once
#include <SFML/Graphics.hpp>

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

	sf::RectangleShape resume;
	sf::RectangleShape exit;
	bool whatSelected = 0;
	bool changeAllowed = true;
	bool escapeAllowed = false;

private:
	unsigned char checkForEnd();
	void displayText();
	void setText();
	void updateText();
	void manageButtons();
	unsigned char pause();
	void display();

public:
	PauseMenu(sf::RenderWindow*, int* score, int* level, int* lines);

	unsigned char checkForPause();
};
