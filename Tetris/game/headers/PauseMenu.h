#pragma once
#include <SFML/Graphics.hpp>

class PauseMenu
{
	sf::RenderWindow* window;
	bool inPause = false;
	bool check = true;

private:
	bool checkKey();
	bool checkForEnd();
	void pause();

public:
	PauseMenu(sf::RenderWindow*);

	bool checkForPause();
};
