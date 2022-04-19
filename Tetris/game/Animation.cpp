#include "headers/Animation.h"

void Animation::set(const std::array<std::array<Cell, ROWS + 2>, COLUMNS>& matrix, float animationTime)
{
	this->animationTime = animationTime;
	setSwitchTime();
	this->texture.loadFromFile("resources/images/animation.png");
	currentTexture.height = INNER_CELL;
	currentTexture.width = INNER_CELL;
	for (unsigned char x = 0; x < COLUMNS; x++)
	{
		for (unsigned char y = 0; y < matrix[0].size(); y++)
		{
			this->spriteMatrix[x][y].setTexture(texture);
			this->spriteMatrix[x][y].setTextureRect(currentTexture);
			this->spriteMatrix[x][y].setPosition(matrix[x][y].getPosition());
		}
	}
}

void Animation::update()
{
	this->switchTime -= DeltaTime::getInstance().getDT();
	if (switchTime <= 0.f)
	{
		setSwitchTime();
		textureChange();
	}
}

void Animation::textureChange()
{
	if (currentTexture.left <= INNER_CELL * 3)
		currentTexture.left += INNER_CELL;
	for (unsigned char x = 0; x < COLUMNS; x++)
	{
		for (unsigned char y = 0; y < spriteMatrix[0].size(); y++)
		{
			this->spriteMatrix[x][y].setTextureRect(currentTexture);
		}
	}
}

void Animation::setSwitchTime()
{
	switchTime = animationTime / 5;
}

void Animation::reset()
{
	currentTexture.left = 0;
	setSwitchTime();
	for (unsigned char x = 0; x < COLUMNS; x++)
	{
		for (unsigned char y = 0; y < spriteMatrix[0].size(); y++)
		{
			this->spriteMatrix[x][y].setTextureRect(currentTexture);
		}
	}
}

void Animation::display(sf::RenderWindow& window, std::vector<int>& linesToDisplay)
{
	if (linesToDisplay.empty())
		return;


	for (int y : linesToDisplay)
	{
		for (unsigned char x = 0; x < COLUMNS; x++)
		{
			window.draw(this->spriteMatrix[x][y]);
		}
	}	
}
