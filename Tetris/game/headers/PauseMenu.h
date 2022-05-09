#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Global.h"

class GameApp;

class PauseMenu
{
	sf::RenderWindow* window;
	bool inPause = false;
	bool check = true;
	sf::Font font;
	sf::Text scoreText;
	sf::Text levelText;
	sf::Text linesText;
	sf::Texture texture;
	sf::Sprite backGround;

	Button* resume;
	Button* exit;
	ButtonManager* buttons;
	bool changeAllowed = true;
	bool escapeAllowed = false;
	GameApp* game;

private:
	void setText();
	void updateText();
	bool checkForEnd();
	void manageButtons();
	void pause();
	void displayText();
	void display();
	void reset();

public:
	PauseMenu(sf::RenderWindow*, GameApp*);
	~PauseMenu();

	void checkForPause();
};
