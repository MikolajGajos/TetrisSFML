#include "Animation.h"

Animation::Animation(const std::array<std::array<Cell, ROWS>, COLUMNS>& matrix, float animationTime)
{
	this->animationTime = animationTime;
	setSwitchTime();
	this->texture.loadFromFile("src/rsrc/animation.png");
	currentTexture.height = 36;
	currentTexture.width = 36;
	for (unsigned char x = 0; x < COLUMNS; x++)
	{
		for (unsigned char y = 0; y < ROWS; y++)
		{
			this->spriteMatrix[x][y].setTexture(texture);
			this->spriteMatrix[x][y].setTextureRect(currentTexture);
			this->spriteMatrix[x][y].setPosition(matrix[x][y].getPosition());
		}
	}	
}

void Animation::update(float deltaTime)
{
	this->switchTime -= deltaTime;
	if (switchTime <= 0.f)
	{
		setSwitchTime();
		textureChange();
	}
}

void Animation::textureChange()
{
	currentTexture.left += 36;
	for (unsigned char x = 0; x < COLUMNS; x++)
	{
		for (unsigned char y = 0; y < ROWS; y++)
		{
			this->spriteMatrix[x][y].setTextureRect(currentTexture);
		}
	}
}

void Animation::setSwitchTime()
{
	switchTime = animationTime / 4;
}

void Animation::reset()
{
	currentTexture.left = 0;
	for (unsigned char x = 0; x < COLUMNS; x++)
	{
		for (unsigned char y = 0; y < ROWS; y++)
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