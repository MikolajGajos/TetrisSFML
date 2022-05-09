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
	int level = 0;
	Button up(0, { 356,200 }, { 200,100 });
	Button down(1, { 356,600 }, { 200,100 });
	sf::Text text;
	sf::Font font;
	font.loadFromFile("resources/images/slkscr.ttf");
	text.setCharacterSize(200);
	text.setFont(font);
	sf::SoundBuffer buffer;
	sf::Sound sound;
	buffer.loadFromFile("resources/sounds/UpDownButtonSound.wav");
	sound.setBuffer(buffer);
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromFile("resources/images/levelSelector.png");
	sprite.setTexture(texture);

	float cooldown = 0.1f;
	bool enterUnpressed = false;

	while (window->isOpen())
	{
		window->clear(sf::Color::Black);

		closingWindowEvent(window);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || up.mouseIntersection(*window))
		{
			if (cooldown > 0.1f && level < 19)
			{
				up.select();
				down.unselect();
				cooldown = 0.f;
				level++;
				sound.play();
			}
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !up.mouseIntersection(*window))
			up.unselect();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || down.mouseIntersection(*window))
		{
			if (cooldown > 0.1f && level > 0)
			{
				down.select();
				up.unselect();
				cooldown = 0.f;
				level--;
				sound.play();
			}			
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !down.mouseIntersection(*window))
			down.unselect();

		if (level < 10)
			text.setPosition({ 390,310 });
		else
			text.setPosition({ 325,310 });
		text.setString(std::to_string(level));

		window->draw(up);
		window->draw(down);
		window->draw(sprite);
		window->draw(text);		

		window->display();
		DeltaTime::getInstance().update();
		cooldown += DeltaTime::getInstance().getDT();
		
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			enterUnpressed = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && enterUnpressed)
			break;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && enterUnpressed)
			return -1;
	}

	return level;
}

int Menu::runGame()
{
	int startringLevel = levelSelector();
	if (startringLevel == -1)
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
