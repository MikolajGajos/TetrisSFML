#include "TextManager.h"

std::string displayLL(int number)
{
	std::ostringstream os;
	os << std::setfill('0') << std::setw(3) << number;	
	return os.str();
}

std::string displayScore(int number)
{
	std::ostringstream os;
	os << std::setfill('0') << std::setw(6) << number;
	return os.str();
}

TextMenager::TextMenager(std::array<std::array<sf::RectangleShape, 22>, 24>* background, int* cleanedLines, int* level, int* score)
{
	this->level = level;
	this->score = score;
	this->clearedLines = cleanedLines;
	this->background = background;
	this->font.loadFromFile("src/rsrc/slkscr.ttf");

	this->clearedLinesText.setCharacterSize(55);
	this->clearedLinesText.setPosition((*background)[13][12].getPosition());
	this->clearedLinesText.setFont(this->font);

	this->levelText.setCharacterSize(55);
	this->levelText.setPosition((*background)[13][14].getPosition());
	this->levelText.setFont(this->font);

	this->scoreText.setCharacterSize(63);
	this->scoreText.setPosition((*background)[13][1].getPosition());
	this->scoreText.setFont(this->font);

	this->nextTetrominoText.setCharacterSize(66);
	this->nextTetrominoText.setPosition((*background)[14][6].getPosition().x - CELL/2, (*background)[14][6].getPosition().y);
	this->nextTetrominoText.setFont(this->font);
	this->nextTetrominoText.setString("next");
}

void TextMenager::updateText()
{
	std::ostringstream ssClenedLines;
	ssClenedLines << "lines - " << displayLL(*this->clearedLines);
	this->clearedLinesText.setString(ssClenedLines.str());

	std::ostringstream ssScore;
	ssScore << "score\n" << displayScore(*this->score);
	this->scoreText.setString(ssScore.str());	

	std::ostringstream ssLevel;
	ssLevel << "level - " << displayLL(*this->level);
	this->levelText.setString(ssLevel.str());
}

void TextMenager::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->clearedLinesText, state);
	target.draw(this->levelText, state);
	target.draw(this->scoreText, state);
	target.draw(this->nextTetrominoText, state);
}

////////////////////////////////////////////////////////////////////////////////////////

BackgroundManager::BackgroundManager()
{
	this->backgroundShape.setSize({ WINDOW_SIZE_X, WINDOW_SIZE_Y });
	this->backgroundTexture.loadFromFile("src/rsrc/Background.png");
	this->backgroundShape.setFillColor(sf::Color::White);
	this->backgroundShape.setTexture(&backgroundTexture);
}

void BackgroundManager::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->backgroundShape);
}
