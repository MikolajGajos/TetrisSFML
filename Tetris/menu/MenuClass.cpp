#include "MenuClass.h"

Menu::Menu()
{
	this->window = new sf::RenderWindow({ WINDOW_SIZE_X, WINDOW_SIZE_Y }, "Tetris", sf::Style::Titlebar | sf::Style::Default);
	this->game = new GameApp(window);
	this->play = new Button(0, sf::Vector2f(250, 500), sf::Vector2f(410, 80));
	this->highscores = new Button(1, sf::Vector2f(250, 600), sf::Vector2f(410, 80));
	this->exit = new Button(2, sf::Vector2f(250, 700), sf::Vector2f(410, 80));
	buttons.set({ *play,*highscores,*exit });
}

Menu::~Menu()
{
	delete window;
	delete game;
	delete play;
	delete highscores;
	delete exit;
}

MenuOutput Menu::getPressedButton()
{
	if (buttons.getSelectedButton() == *play)
		return MenuOutput::play;
	else if (buttons.getSelectedButton() == *highscores)
		return MenuOutput::highscores;
	else if (buttons.getSelectedButton() == *exit)
		return MenuOutput::exit;
}

bool Menu::checkIfButtonPressed()
{
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

MenuOutput Menu::userInput()
{
	if (checkIfButtonPressed())
		return (getPressedButton());
	else return MenuOutput::noImput;
}

void Menu::update()
{
	while (window->isOpen())
	{
		sf::Event event;
		(*window).pollEvent(event);
		if (event.type == sf::Event::Closed)
			(*window).close();

		buttons.update(*window);
		switch (userInput())
		{
		case MenuOutput::play:
			runGame();
			break;
		case MenuOutput::highscores:
			//to do
			break;
		case MenuOutput::exit:
			return;
		case MenuOutput::noImput:
			break;
		}
		display();
	}
}

int Menu::runGame()
{
	game->setStartingLevel(0); // to do
	return game->run();
}

void Menu::display()
{
	window->clear(sf::Color::Black);
	window->draw(buttons);
	window->display();
}
