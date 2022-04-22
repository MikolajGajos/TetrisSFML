#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Button : public sf::Drawable
{
	sf::RectangleShape buttonShape;
	bool selected = false;
	int id;

public:
	Button() {};
	Button(int id, int posX, int posY, int sizeX, int sizeY);

	int getID() const;
	void select();
	bool isSelected();
	void unselect();
	bool mouseIntersection(sf::RenderWindow& window);
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	bool operator== (Button& but); 
};

//////////////////////////////////////////////////////////////////////////////////////////

class ButtonManager : public sf::Drawable
{
	Button* buttonArray;
	int arraySize;
	Button* selectedButton;
	bool legalChange = true;

public:
	ButtonManager(std::initializer_list<Button> li);
	~ButtonManager();

	void update(sf::RenderWindow& window);
	void selectButton(Button& but);
	Button getSelectedButton();
	void selectNext();
	void selectPrevoius();
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};