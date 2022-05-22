#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <functional>

class Button : public sf::Drawable
{
	sf::RectangleShape buttonShape;
	bool selected = false;
	int id;
	std::function<void()> onClickFunction = nullptr;

public:
	Button() {};
	Button(int id, sf::Vector2f position, sf::Vector2f size);

	void setOnClickFunction(std::function<void()> function);
	void onClick();

	int getID() const;
	void select();
	bool isSelected();
	void unselect();
	bool mouseIntersection(sf::RenderWindow& window);
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	bool isClicked(sf::RenderWindow& window);

	bool operator== (Button& but); 
};

//////////////////////////////////////////////////////////////////////////////////////////

class ButtonManager : public sf::Drawable
{
	Button* buttonArray;
	int arraySize;
	Button* selectedButton;
	bool legalChange = true;
	sf::SoundBuffer buffer;
	sf::Sound sound;

private:
	void selectButton(Button& but);
	void selectNext();
	void selectPrevoius();
	void playSoundIfButtonChanged(Button& b1, Button& b2);

public:
	ButtonManager(std::initializer_list<Button> li);
	~ButtonManager();

	bool mouseIntersects(sf::RenderWindow& window);
	void pressButton(Button&);
	Button getSelectedButton();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	void reset();

	void setVolume(int val);
};