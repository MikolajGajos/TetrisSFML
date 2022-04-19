#include "headers/PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow* window) : window(window)
{

}

bool PauseMenu::checkKey()
{
	return(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
}

bool PauseMenu::checkForPause()
{
	if (checkKey())
	{
		check = false;
		pause();
		return true;
	}
	return false;
}

bool PauseMenu::checkForEnd()
{
	if (!check)
	{
		check = !checkKey();
		return false;
	}
	return checkKey();
}

void PauseMenu::pause()
{
	while (window->isOpen())
	{
		window->clear(sf::Color::Black);
		window->display();


		
		if (checkForEnd())
			return;
	}
}


