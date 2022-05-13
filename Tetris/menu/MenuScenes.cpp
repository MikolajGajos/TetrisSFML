#include "MenuClass.h"

Menu::LvlSelector::LvlSelector()
{
	up = new Button(0, { 356,200 }, { 200,100 });
	down = new Button(1, { 356,600 }, { 200,100 });
	font.loadFromFile("resources/images/slkscr.ttf");
	text.setCharacterSize(200);
	text.setFont(font);
	buffer.loadFromFile("resources/sounds/UpDownButtonSound.wav");
	sound.setBuffer(buffer);
	texture.loadFromFile("resources/images/levelSelector.png");
	sprite.setTexture(texture);
}

Menu::LvlSelector::~LvlSelector()
{
	delete up;
	delete down;
}

void Menu::LvlSelector::incrementLevel()
{
	if (cooldown < 0.1f || level > 19)
		return;
	up->select();
	down->unselect();
	cooldown = 0.f;
	level++;
	sound.play();
}

void Menu::LvlSelector::decrementLevel()
{
	if (cooldown < 0.1f || level <= 0)
		return;
	down->select();
	up->unselect();
	cooldown = 0.f;
	level--;
	sound.play();
}

void Menu::LvlSelector::userInput(sf::RenderWindow* window)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		enterUnpressed = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || up->isClicked(*window))
	{
		incrementLevel();
	}
	else
		up->unselect();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || down->isClicked(*window))
	{
		decrementLevel();
	}
	else
		down->unselect();
}

void Menu::LvlSelector::display(sf::RenderWindow* window)
{
	if (level < 10)
		text.setPosition({ 390,310 });
	else
		text.setPosition({ 325,310 });
	text.setString(std::to_string(level));

	window->draw(*up);
	window->draw(*down);
	window->draw(sprite);
	window->draw(text);
}
