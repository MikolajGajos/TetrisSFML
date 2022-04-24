#include "headers/Button.h"

Button::Button(int id, int posX, int posY, int sizeX, int sizeY)
{
	this->buttonShape.setPosition({ (float)posX,(float)posY });
	this->buttonShape.setSize({ (float)sizeX, (float)sizeY });
	this->id = id;
}

void Button::set(int id, int posX, int posY, int sizeX, int sizeY)
{
	this->buttonShape.setPosition({ (float)posX,(float)posY });
	this->buttonShape.setSize({ (float)sizeX, (float)sizeY });
	this->id = id;
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
}

void ButtonManager::set(std::initializer_list<Button> li)
{
	this->buttonArray = new Button[li.size()];
	this->arraySize = li.size();
	for (auto& but : li)
	{
		this->buttonArray[but.getID()] = but;
	}
	this->selectedButton = &this->buttonArray[0];
	this->buttonArray[0].select();
}

ButtonManager::~ButtonManager()
{
	delete[] buttonArray;
}

void ButtonManager::update(sf::RenderWindow& window)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (buttonArray[i].mouseIntersection(window))
		{
			selectedButton->unselect();
			buttonArray[i].select();
			selectButton(buttonArray[i]);
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
		legalChange = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		selectPrevoius();
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


