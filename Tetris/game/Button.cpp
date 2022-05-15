#include "headers/Button.h"

Button::Button(int id, sf::Vector2f position, sf::Vector2f size)
{
	this->buttonShape.setPosition({ position });
	this->buttonShape.setSize({ size });
	this->id = id;
}

void Button::setOnClickFunction(std::function<void()> function)
{
	this->onClickFunction = function;
}

void Button::onClick()
{
	if(onClickFunction != nullptr)
		onClickFunction();
}

int Button::getID() const
{
	return id;
}

void Button::select()
{
	selected = true;
	buttonShape.setFillColor(sf::Color::Red);
}

bool Button::isSelected()
{
	return selected;
}

void Button::unselect()
{
	this->selected = false;
	this->buttonShape.setFillColor(sf::Color::White);
}

bool Button::mouseIntersection(sf::RenderWindow& window)
{
	if (buttonShape.getGlobalBounds().contains((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y))
		return true;
	return false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(buttonShape);
}

bool Button::operator==(Button& but)
{
	if (this->getID() == but.getID())
		return true;
	return false;
}

bool Button::isClicked(sf::RenderWindow& window)
{
	if (mouseIntersection(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////

ButtonManager::ButtonManager(std::initializer_list<Button> li)
{
	this->buttonArray = new Button[li.size()];
	this->arraySize = li.size();
	for (auto& but : li)
	{
		this->buttonArray[but.getID()] = but;
	}
	this->selectedButton = &this->buttonArray[0];
	this->buttonArray[0].select();
	this->buffer.loadFromFile("resources/sounds/ButtonSound.wav");
	this->sound.setBuffer(buffer);
}

ButtonManager::~ButtonManager()
{
	delete[] buttonArray;
}

void ButtonManager::playSoundIfButtonChanged(Button& b1, Button& b2)
{
	if (b1 != b2)
		sound.play();
}

void ButtonManager::update(sf::RenderWindow& window)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (buttonArray[i].mouseIntersection(window))
		{
			Button b = *selectedButton;
			selectedButton->unselect();
			buttonArray[i].select();
			selectButton(buttonArray[i]);
			playSoundIfButtonChanged(b, *selectedButton);
			return;
		}
	}

	if (!legalChange)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			legalChange = true;
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		selectNext();
		sound.play();
		legalChange = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		selectPrevoius();
		sound.play();
		legalChange = false;
	}
}

void ButtonManager::selectButton(Button& but)
{
	this->selectedButton = &but;
}

bool ButtonManager::mouseIntersects(sf::RenderWindow& window)
{
	if (getSelectedButton().mouseIntersection(window))
		return true;
	return false;
}

void ButtonManager::pressButton(Button& but)
{
	selectedButton->unselect();
	selectedButton = &but;
	selectedButton->select();
}

Button ButtonManager::getSelectedButton()
{
	return *selectedButton;
}

void ButtonManager::selectNext()
{
	buttonArray[getSelectedButton().getID()].unselect();
	if (getSelectedButton().getID() < arraySize - 1)
	{
		buttonArray[getSelectedButton().getID() + 1].select();
		selectButton(buttonArray[getSelectedButton().getID() + 1]);
	}
	else
	{
		buttonArray[0].select();
		selectButton(buttonArray[0]);
	}
}

void ButtonManager::selectPrevoius()
{
	buttonArray[getSelectedButton().getID()].unselect();
	if (getSelectedButton().getID() != 0)
	{
		buttonArray[getSelectedButton().getID() - 1].select();
		selectButton(buttonArray[getSelectedButton().getID() - 1]);
	}
	else
	{
		buttonArray[arraySize - 1].select();
		selectButton(buttonArray[arraySize - 1]);
	}
}

void ButtonManager::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (int i = 0; i < arraySize; i++)
	{
		target.draw(buttonArray[i]);
	}
}

void ButtonManager::reset()
{
	pressButton(buttonArray[0]);
}

void ButtonManager::setVolume(int val)
{
	sound.setVolume(val);
}
