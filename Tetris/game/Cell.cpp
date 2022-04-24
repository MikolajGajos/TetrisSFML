#include "headers/Cell.h"

Cell::Cell()
{
	this->full = false;
	this->cellShape.setSize(sf::Vector2f(INNER_CELL, INNER_CELL));
	this->texture.loadFromFile("resources/images/Tile.png");
	this->cellShape.setTexture(&texture);
}

void Cell::setColor(const sf::Color& color)
{
	this->color = color;
	this->cellShape.setFillColor(this->color);
}

sf::Color Cell::getColor()
{
	return this->color;
}

void Cell::setPosition(const sf::Vector2f& position)
{
	float x = position.x;
	float y = position.y;
	this->cellShape.setPosition({ x,y });
}

sf::Vector2f Cell::getPosition() const
{
	return this->cellShape.getPosition();
}

void Cell::setFull(const bool b)
{
	this->full = b;
}

void Cell::setTexture(const sf::Texture& texture)
{
	this->cellShape.setTexture(&texture);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->cellShape, state);
}
