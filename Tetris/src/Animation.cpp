#include "Animation.h"

Animation::Animation(const std::array<std::array<Cell, ROWS>, COLUMNS>& matrix)
{
	this->switchTime = 0.5f;

	this->texture.loadFromFile("src/rsrc/Tile.png");
	for (unsigned char i = 0; i < ROWS; i++)
	{
		this->rows[i].setSize({CELL * COLUMNS, CELL});
		this->rows[i].setPosition(matrix[0][i].getPosition());
		this->rows[i].setTexture(&this->texture);
		this->rows[i].setFillColor(sf::Color::White);
	}
}

void Animation::display(sf::RenderWindow& window, std::vector<int>& linesToDisplay)
{
	if (linesToDisplay.empty())
		return;

	for (int y : linesToDisplay)
	{
		window.draw(this->rows[y]);
	}
}