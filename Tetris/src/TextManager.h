#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include <array>
#include <string>

#include "Global.h"

class TextManager : public sf::Drawable
{
	std::array<std::array<sf::RectangleShape, 22>, 24>* background;
	int* clearedLines;
	int* score;
	int* level;
	sf::Font font;

public:
	sf::Text clearedLinesText;
	sf::Text levelText;
	sf::Text scoreText;
	sf::Text nextTetrominoText;

	TextManager();

public:
	static TextManager& getInstance()
	{
		static TextManager instance;
		return instance;
	}
	void set(std::array<std::array<sf::RectangleShape, 22>, 24>* matrix, int* clearedLines, int* level, int* score);
	void updateText();

	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

class BackgroundManager : public sf::Drawable
{
	sf::RectangleShape backgroundShape;
	sf::Texture backgroundTexture;

	BackgroundManager();

public:
	static BackgroundManager& getInstance()
	{
		static BackgroundManager instance;
		return instance;
	}
	
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};
