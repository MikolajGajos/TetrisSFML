#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../game/headers/Button.h"
#include "../game/headers/GameApp.h"

class Menu
{
	sf::RenderWindow* window;
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	GameApp* game;
	Button* play;
	Button* highscores;
	Button* options;
	Button* exit;
	ButtonManager* buttons;

private:
	bool checkIfButtonPressed();
	int runGame();
	int levelSelector();
	void display();
	void close();

public:
	Menu();
	~Menu();
	int exitGame();
	void update();
};
