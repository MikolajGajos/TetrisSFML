#include "headers/PauseMenu.h"
#include "headers/GameApp.h"

void closingWindowEvent(sf::RenderWindow* window);

PauseMenu::PauseMenu(sf::RenderWindow* window, GameApp* game) : window(window)
{
	this->game = game;
	this->setText();
	this->texture.loadFromFile("resources/images/PauseMenu.png");
	this->backGround.setTexture(texture);
	this->resume = new Button(0, sf::Vector2f(250, 180), sf::Vector2f(410, 120));
	this->resume->setOnClickFunction(std::bind(&GameApp::resume, this->game));
	this->exit = new Button(1, sf::Vector2f(250, 380), sf::Vector2f(410, 120));
	this->exit->setOnClickFunction(std::bind(&GameApp::exitGame, this->game));
	this->buttons = new ButtonManager({ *resume,*exit });
	this->buttons->update(*window);
}

PauseMenu::~PauseMenu()
{
	delete resume;
	delete exit;
	delete buttons;
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
	this->scoreText.setString("score: " + std::to_string(game->score));
	this->levelText.setString("level: " + std::to_string(game->level));
	this->linesText.setString("lines: " + std::to_string(game->clearedLines));
}

void PauseMenu::checkForPause()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		check = false;	
		this->pause();
	}
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
			buttons->pressButton(*resume);
			return true;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		return true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (buttons->mouseIntersects(*window))
			return true;
	}
	return false;
}

void PauseMenu::manageButtons()
{
	buttons->update(*window);
}

void PauseMenu::pause()
{
	updateText();

	while (window->isOpen())
	{
		closingWindowEvent(window);

		if (checkForEnd())
		{
			reset();
			buttons->getSelectedButton().onClick();
			break;
		}

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
	window->draw(*buttons);
	window->draw(backGround);
	displayText();
	window->display();
}

void PauseMenu::reset()
{
	changeAllowed = true;
	escapeAllowed = false;
}
