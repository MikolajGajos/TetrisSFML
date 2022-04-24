#include "headers/Animation.h"

Animation::Animation(std::array<std::array<Cell, ROWS + 2>, COLUMNS>& gameBoard, float animationTime)
{
	this->gameBoard = &gameBoard;
	this->animationTime = animationTime;
	this->animationDelta = animationTime;
	this->setSwitchTime();
	this->texture.loadFromFile("resources/images/animation.png");
	this->currentTexture.height = INNER_CELL;
	this->currentTexture.width = INNER_CELL;
	for (unsigned char x = 0; x < gameBoard.size(); x++)
	{
		for (unsigned char y = 0; y < gameBoard[x].size(); y++)
		{
			this->animationBoard[x][y].setTexture(texture);
			this->animationBoard[x][y].setTextureRect(currentTexture);
			this->animationBoard[x][y].setPosition(gameBoard[x][y].getPosition());
		}
	}
}

bool Animation::update()
{
	DeltaTime::getInstance().update();
	switchTime -= DeltaTime::getInstance().getDT();
	if (switchTime <= 0.f)
	{
		setSwitchTime();
		textureChange();
	}
	animationDelta -= DeltaTime::getInstance().getDT();
	if (animationDelta <= 0.f)
		return true;

	return false;
}

void Animation::textureChange()
{
	if (currentTexture.left <= INNER_CELL * 3)
		currentTexture.left += INNER_CELL;
	for (unsigned char x = 0; x < COLUMNS; x++)
	{
		for (unsigned char y = 0; y < animationBoard[0].size(); y++)
		{
			this->animationBoard[x][y].setTextureRect(currentTexture);
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
	animationDelta = animationTime;
	for (unsigned char x = 0; x < COLUMNS; x++)
	{
		for (unsigned char y = 0; y < animationBoard[0].size(); y++)
		{
			this->animationBoard[x][y].setTextureRect(currentTexture);
		}
	}
}

void Animation::drawBoard(sf::RenderWindow* window)
{
	sf::Texture emptyTexture;
	emptyTexture.loadFromFile("resources/images/GameBackground.png");
	sf::Sprite sprite;
	sprite.setTexture(emptyTexture);
	sprite.setColor(sf::Color(70, 70, 70));

	for (unsigned char i = 0; i < (*gameBoard).size(); i++)
	{
		for (unsigned char j = 2; j < (*gameBoard)[i].size(); j++)
		{
			if ((*gameBoard)[i][j].isFull())
			{
				window->draw((*gameBoard)[i][j]);
			}
			else
			{
				sprite.setPosition((*gameBoard)[i][j].getPosition());
				window->draw(sprite);
			}
		}
	}
}

void Animation::display(sf::RenderWindow* window, std::vector<int> linesToDisplay)
{
	while (window->isOpen())
	{
		if (update())
		{
			reset();
			return;
		}
		drawBoard(window);
		for (int y : linesToDisplay)
		{
			for (unsigned char x = 0; x < COLUMNS; x++)
			{
				window->draw(this->animationBoard[x][y]);
			}
		}
		window->display();
	}
	
}
