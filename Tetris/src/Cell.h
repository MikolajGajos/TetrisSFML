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
	Cell(const sf::Color&);
	Cell(const sf::Vector2f&);
	void setColor(const sf::Color&);
	sf::Color getColor();
	void setPosition(const sf::Vector2f&);
	sf::Vector2f getPosition() const;
	bool isFull() const { return this->full; }
	void setFull(const bool);
	void setTexture(const sf::Texture&);

	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};