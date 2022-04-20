#include "headers/PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow* window, int* score, int* level, int* lines) : window(window)
{
	this->score = score;
	this->level = level;
	this->lines = lines;
	setText();
	this->texture.loadFromFile("resources/images/PauseMenu.png");
	this->backGround.setTexture(texture);

	this->resume.setSize({ 410,120 });
	this->resume.setPosition(250, 180);
	this->exit.setSize({ 410,120 });
	this->exit.setPosition(250, 380);
}

unsigned char PauseMenu::checkForPause()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		check = false;	
		return pause();
	}
	return 0;
}

unsigned char PauseMenu::checkForEnd()
{
	if (!escapeAllowed)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			escapeAllowed = true;
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			escapeAllowed = false;
			return 1;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		switch (whatSelected)
		{
		case 0:
			return 1;
		case 1:
			return 2;
		}
	}
	return 0;
}

void PauseMenu::displayText()
{
	window->draw(scoreText);
	window->draw(linesText);
	window->draw(levelText);
}

void PauseMenu::setText()
{
	this->font.loadFromFile("resources/images/slkscr.ttf");
	this->scoreText.setCharacterSize(30);
	this->scoreText.setFont(font);
	this->scoreText.setPosition({ 0,0 });

	this->levelText.setCharacterSize(30);
	this->levelText.setFont(font);
	this->levelText.setPosition({ 0,40 });

	this->linesText.setCharacterSize(30);
	this->linesText.setFont(font);
	this->linesText.setPosition({ 0,80 });
}

void PauseMenu::updateText()
{
	this->scoreText.setString("score: " + std::to_string(*score));
	this->levelText.setString("level: " + std::to_string(*level));
	this->linesText.setString("lines: " + std::to_string(*lines));
}

void PauseMenu::manageButtons()
{
	if (!changeAllowed)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			changeAllowed = true;
		return;
	}	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		changeAllowed = false;
		whatSelected = !whatSelected;
	}

	switch (whatSelected)
	{
	case 0:
		resume.setFillColor(sf::Color::Red);
		exit.setFillColor(sf::Color::White);
		break;
	case 1:
		resume.setFillColor(sf::Color::White);
		exit.setFillColor(sf::Color::Red);
		break;
	}
}

unsigned char PauseMenu::pause()
{
	updateText();

	while (window->isOpen())
	{
		sf::Event event;
		(*window).pollEvent(event);
		if (event.type == sf::Event::Closed)
			(*window).close();

		manageButtons();

		display();
		
		unsigned char c = checkForEnd();
		if (c != 0)
			return c;
	}
}

void PauseMenu::display()
{
	window->clear(sf::Color::Black);
	window->draw(resume);
	window->draw(exit);
	window->draw(this->backGround);
	displayText();
	window->display();
}
