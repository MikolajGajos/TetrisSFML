#include "headers/PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* window, int* score, int* level, int* lines) : window(window)
{
	this->score = score;
	this->level = level;
	this->lines = lines;
	setText();
	this->texture.loadFromFile("resources/images/PauseMenu.png");
	this->backGround.setTexture(texture);
	resume = new Button(0, sf::Vector2f(250, 180), sf::Vector2f(410, 120));
	exit = new Button(1, sf::Vector2f(250, 380), sf::Vector2f(410, 120));
	buttons.set({ *resume,*exit });
	buttons.update(*window);
}

PauseMenu::~PauseMenu()
{
	delete resume;
	delete exit;
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

PauseOutput PauseMenu::checkForPause()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		check = false;	
		return pause();
	}
	return PauseOutput::noPause;
}

bool PauseMenu::checkForEnd()
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
			buttons.pressButton(*resume);
			return true;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		return true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (buttons.mouseIntersects(*window))
			return true;
	}
	return false;
}

void PauseMenu::manageButtons()
{
	buttons.update(*window);
}

PauseOutput PauseMenu::getPressedButton()
{
	if (buttons.getSelectedButton() == *resume)
		return PauseOutput::resume;
	else
		return PauseOutput::exit;
}

PauseOutput PauseMenu::pause()
{
	updateText();

	while (window->isOpen())
	{
		sf::Event event;
		(*window).pollEvent(event);
		if (event.type == sf::Event::Closed)
			(*window).close();

		if (checkForEnd())
			return getPressedButton();

		manageButtons();

		display();		
		DeltaTime::getInstance().update();
	}
}

void PauseMenu::displayText()
{
	window->draw(scoreText);
	window->draw(linesText);
	window->draw(levelText);
}

void PauseMenu::display()
{
	window->clear(sf::Color::Black);
	window->draw(buttons);
	window->draw(this->backGround);
	displayText();
	window->display();
}
