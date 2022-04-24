#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include <array>
#include <string>

#include "Global.h"

class GameText : public sf::Drawable
{
	int* clearedLines;
	int* score;
	int* level;
	sf::Font font;
	sf::Text clearedLinesText;
	sf::Text levelText;
	sf::Text scoreText;
	sf::Text nextTetrominoText;


public:
	GameText();
	void set(std::array<std::array<sf::RectangleShape, 22>, 24>& matrix, int& clearedLines, int& level, int& score);
	void updateText();

	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

class GameBackground
{
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture gameOverTexture;
	sf::Sprite gameOverSprite;


public:
	GameBackground();
	
	void displayBackground(sf::RenderWindow* window);
	void displayGameOver(sf::RenderWindow* window);
};
