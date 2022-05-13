#include "MenuClass.h"

void closingWindowEvent(sf::RenderWindow* window);

Menu::Menu()
{
	this->window = new sf::RenderWindow({ WINDOW_SIZE_X, WINDOW_SIZE_Y }, "Tetris", sf::Style::Titlebar | sf::Style::Close);
	this->game = new GameApp(window);
	this->menuTexture.loadFromFile("resources/images/Menu.png");
	this->menuSprite.setTexture(menuTexture);
	this->play = new Button(0, sf::Vector2f(250, 400), sf::Vector2f(410, 80));
	this->play->setOnClickFunction(std::bind(&Menu::runGame, this));
	this->highscores = new Button(1, sf::Vector2f(250, 500), sf::Vector2f(410, 80));
	this->options = new Button(2, sf::Vector2f(250, 600), sf::Vector2f(410, 80));
	this->exit = new Button(3, sf::Vector2f(250, 700), sf::Vector2f(410, 80));
	this->exit->setOnClickFunction(std::bind(&Menu::close, this));
	this->buttons = new ButtonManager({ *play,*highscores,*options,*exit });
}

Menu::~Menu()
{
	delete window;
	delete game;
	delete play;
	delete highscores;
	delete options;
	delete exit;
	delete buttons;
}

bool Menu::checkIfButtonPressed()
{
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

void Menu::update()
{
	while (window->isOpen())
	{
		closingWindowEvent(window);

		buttons->update(*window);

		if (checkIfButtonPressed())
			buttons->getSelectedButton().onClick();

		display();
	}
}

int Menu::levelSelector()
{
	while (window->isOpen())
	{
		closingWindowEvent(window);
		levelSelctor.userInput(window);
		levelSelctor.display(window);
		window->display();

		DeltaTime::getInstance().update();
		levelSelctor.cooldown += DeltaTime::getInstance().getDT();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && levelSelctor.enterUnpressed)
			break;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && levelSelctor.enterUnpressed)
			return -1;
	}
	return levelSelctor.level;
}

int Menu::runGame()
{
	int startringLevel = levelSelector();
	if (startringLevel < 0)
		return 0;
	game->setStartingLevel(startringLevel); 
	game->run();
	return exitGame();
}

int Menu::exitGame()
{
	int score = game->score;
	delete game;
	game = new GameApp(window);
	return score;
}

void Menu::display()
{
	window->clear(sf::Color::Black);
	window->draw(*buttons);
	window->draw(menuSprite);
	window->display();
}

void Menu::close()
{
	window->close();
}
