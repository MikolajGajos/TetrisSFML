#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "Global.h"
#include "Cell.h"

class Animation
{
	sf::Texture texture;
	std::array<std::array<sf::Sprite, ROWS>, COLUMNS> spriteMatrix;
	sf::IntRect currentTexture;
	float animationTime;
	float switchTime;		

private:
	void textureChange();
	void setSwitchTime();

public:
	Animation() {};
	Animation(const std::array<std::array<Cell, ROWS>, COLUMNS>&, float animationTime);

	void update(float deltaTime);
	
	void reset();

	void display(sf::RenderWindow&, std::vector<int>& linesToDisplay);
};