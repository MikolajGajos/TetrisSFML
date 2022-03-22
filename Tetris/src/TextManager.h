#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include <array>
#include <string>

#include "Global.h"

class TextMenager : public sf::Drawable
{
	std::array<std::array<sf::RectangleShape, 22>, 24>* background;
	int* clearedLines;

	sf::Font font;

public:
	sf::Text clearedLinesText;
	sf::Text levelText;
	sf::Text scoreText;
	sf::Text nextTetrominoText;

public:
	TextMenager(std::array<std::array<sf::RectangleShape, 22>, 24>* background, int* cleanedLines);
	void updateText();

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};
