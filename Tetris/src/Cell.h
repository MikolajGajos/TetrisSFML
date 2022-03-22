#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Cell : public sf::Drawable
{
	sf::Color color;
	sf::RectangleShape cellShape;
	bool full;
public:

	Cell();
	Cell(const sf::Color& color);
	Cell(const sf::Vector2f& position);
	void setColor(const sf::Color& color);
	sf::Color getColor();
	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition();
	bool isFull() const { return this->full; }
	void setFull(const bool b);
	void setTexture(const sf::Texture& texture);

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};