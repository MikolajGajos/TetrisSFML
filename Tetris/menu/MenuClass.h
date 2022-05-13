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

	class LvlSelector
	{
	public:
		int level = 0;
		Button* up;
		Button* down;
		sf::Text text;
		sf::Font font;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		sf::Sprite sprite;
		sf::Texture texture;
		float cooldown = 0.1f;
		bool enterUnpressed = false;

		LvlSelector();
		~LvlSelector();
		void incrementLevel();
		void decrementLevel();
		void userInput(sf::RenderWindow* window);
		void display(sf::RenderWindow* window);
	} levelSelctor;

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
