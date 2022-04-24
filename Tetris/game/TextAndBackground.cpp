#include "headers/TextAndBackground.h"

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

GameText::GameText()
{
	font.loadFromFile("resources/images/slkscr.ttf");

	clearedLinesText.setCharacterSize(55);
	clearedLinesText.setFont(this->font);

	levelText.setCharacterSize(55);
	levelText.setFont(this->font);

	scoreText.setCharacterSize(63);
	scoreText.setFont(this->font);

	nextTetrominoText.setCharacterSize(66);
	nextTetrominoText.setFont(this->font);
	nextTetrominoText.setString("next");
}

void GameText::set(std::array<std::array<sf::RectangleShape, 22>, 24>& background, int& clearedLines, int& level, int& score)
{
	this->level = &level;
	this->score = &score;
	this->clearedLines = &clearedLines;

	this->clearedLinesText.setPosition(background[13][12].getPosition());
	this->levelText.setPosition(background[13][14].getPosition());
	this->scoreText.setPosition(background[13][1].getPosition());
	this->nextTetrominoText.setPosition(background[14][6].getPosition().x - CELL_SIZE / 2, background[14][6].getPosition().y);

	updateText();
}

void GameText::updateText()
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

void GameText::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->clearedLinesText, state);
	target.draw(this->levelText, state);
	target.draw(this->scoreText, state);
	target.draw(this->nextTetrominoText, state);
}

////////////////////////////////////////////////////////////////////////////////////////

GameBackground::GameBackground()
{
	this->backgroundTexture.loadFromFile("resources/images/Background.png");
	this->backgroundSprite.setTexture(backgroundTexture);
	this->gameOverTexture.loadFromFile("resources/images/GameOver.png");
	this->gameOverSprite.setTexture(gameOverTexture);
}

void GameBackground::displayBackground(sf::RenderWindow* window)
{
	window->draw(backgroundSprite);
}

void GameBackground::displayGameOver(sf::RenderWindow* window)
{
	window->draw(gameOverSprite);
}

