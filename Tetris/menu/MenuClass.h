#pragma once
#include "SFML/Graphics.hpp"
#include "../game/headers/Button.h"
#include "../game/headers/GameApp.h"

enum class MenuOutput
{
	play, highscores, options, exit, noImput
};

class Menu
{
	sf::RenderWindow* window;
	GameApp* game;
	Button* play;
	Button* highscores;
	Button* options;
	Button* exit;
	ButtonManager* buttons;
	MenuOutput getPressedButton();
	bool checkIfButtonPressed();
	MenuOutput userInput();
	int runGame();
	void display();

public:
	Menu();
	~Menu();
	void update();
};
