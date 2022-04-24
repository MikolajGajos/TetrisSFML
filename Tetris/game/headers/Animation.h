#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "Global.h"
#include "Cell.h"

class Animation
{
	sf::Texture texture;
	std::array<std::array<sf::Sprite, ROWS + 2>, COLUMNS> animationBoard;
	std::array<std::array<Cell, ROWS + 2>, COLUMNS>* gameBoard;
	sf::IntRect currentTexture;
	float animationTime;
	float animationDelta;
	float switchTime;		
	

private:
	void textureChange();
	void setSwitchTime();

public:
	Animation(std::array<std::array<Cell, ROWS + 2>, COLUMNS>&, float animationTime);

	bool update();	
	void reset();
	void drawBoard(sf::RenderWindow* window);
	void display(sf::RenderWindow*, std::vector<int> linesToDisplay);
};