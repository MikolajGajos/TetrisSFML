#include "MenuClass.h"

void closingWindowEvent(sf::RenderWindow* window);

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

Menu::OptionsMenu::OptionsMenu()
{
	menuDown = new Button(0, { 200,100 }, { 100,100 });
	menuDown->setOnClickFunction(std::bind(&Menu::OptionsMenu::decrementMenu, this));
	menuUp = new Button(1, { 612,100 }, { 100,100 });

	effectsDown = new Button(2, { 200,300 }, { 100,100 });
	effectsDown->setOnClickFunction(std::bind(&Menu::OptionsMenu::decrementEffects, this));
	menuUp->setOnClickFunction(std::bind(&Menu::OptionsMenu::incrementMenu, this));
	effectsUp = new Button(3, { 612,300 }, { 100,100 });

	effectsUp->setOnClickFunction(std::bind(&Menu::OptionsMenu::incrementEffects, this));
	musicDown = new Button(4, { 200,500 }, { 100,100 });
	musicDown->setOnClickFunction(std::bind(&Menu::OptionsMenu::decrementMusic, this));
	musicUp = new Button(5, { 612,500 }, { 100,100 });
	musicUp->setOnClickFunction(std::bind(&Menu::OptionsMenu::incrementMusic, this));

	Controls = new Button(6, { 600,700 }, { 200,100 });
	Controls->setOnClickFunction(std::bind(&Menu::OptionsMenu::displayControls, this));
	buttons = new ButtonManager({ *menuUp, *menuDown, *effectsUp, *effectsDown, *musicUp, *musicDown, *Controls });

	font.loadFromFile("resources/images/slkscr.ttf");
	menuText.setCharacterSize(50);
	menuText.setFont(font);
	menuText.setPosition(400, 100);
	effectsText.setCharacterSize(50);
	effectsText.setFont(font);
	effectsText.setPosition(400, 300);
	musicText.setCharacterSize(50);
	musicText.setFont(font);
	musicText.setPosition(400, 500);
}

Menu::OptionsMenu::~OptionsMenu()
{
	delete menuUp;
	delete menuDown;
	delete effectsUp;
	delete effectsDown;
	delete musicUp;
	delete musicDown;
	delete Controls;
	delete buttons;
}

void Menu::OptionsMenu::updateText()
{
	menuText.setString(std::to_string(SoundVolume::getInstance().getVolume(Volume::menu)));
	musicText.setString(std::to_string(SoundVolume::getInstance().getVolume(Volume::music)));
	effectsText.setString(std::to_string(SoundVolume::getInstance().getVolume(Volume::effects)));
}

void Menu::OptionsMenu::changeVolumeOpt(Volume vol, int val)
{
	SoundVolume::getInstance().changeVolume(vol, val);
}

void Menu::OptionsMenu::displayControls()
{
	while (window->isOpen())
	{
		closingWindowEvent(window);

		window->clear();
		window->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;
	}
}

void Menu::OptionsMenu::display(sf::RenderWindow* window)
{
	window->draw(menuText);
	window->draw(musicText);
	window->draw(effectsText);
	window->draw(*buttons);
}
