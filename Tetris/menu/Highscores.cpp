#include "MenuClass.h"
#include <filesystem>
#include <fstream>
#include <regex>
#include <iomanip>

constexpr int BACKSPACE = 8;
constexpr int ENTER = 13;
constexpr int ESC = 27;

class TextBox
{
    sf::Text text;
    sf::Font font;
    std::string name;
    float timer = 0.f;
    bool showSlash = false;

public:
    TextBox(sf::Vector2f position, int size, sf::RenderWindow* window)
    {
        font.loadFromFile("resources/images/slkscr.ttf");
        text.setPosition(position);
        text.setFont(font);
        text.setCharacterSize(size);
        update(window);
    }

    void update(sf::RenderWindow* window)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::TextEntered:
                updateText(event);
                break;
            }
        }
        slashMangement();
    }

    void slashMangement()
    {
        DeltaTime::getInstance().update();
        timer += DeltaTime::getInstance().getDT();
        if (timer < 0.5f)
            showSlash = true;
        else
        {
            showSlash = false;
            if(timer > 1.f)
                timer = 0.f;
        }
    }

    void updateText(sf::Event event)
    {
        if (event.text.unicode == BACKSPACE && name.size() > 0)
            name.pop_back();
        else if (event.text.unicode != BACKSPACE && event.text.unicode != ENTER && event.text.unicode != ESC && name.size() < 10)
            name.push_back(event.text.unicode);

        text.setString(name);
        timer = 0.f;
        if (!validName())
            text.setFillColor(sf::Color::Red);
        else
            text.setFillColor(sf::Color::White);
    }

    bool validName()
    {
        std::regex nameReg("[0-9A-Za-z]{3,10}");
        return std::regex_match(name, nameReg);
    }

    sf::Text getText()
    {
        if (showSlash)
            text.setString(name + "|");
        else
            text.setString(name);
        return text;
    }
    std::string* getName()
    {
        return &name;
    }
};

void HighscoreManager::highscores::saveSocore(std::pair<int, std::string> score)
{
	std::array < std::pair<int, std::string>, 5> temp = arr;
	for (unsigned char i = 0; i < arr.size(); i++)
	{
		if (score.first > arr[i].first)
		{
			for (unsigned char j = i + 1; j < arr.size(); j++)
			{
				temp[j].first = arr[j - 1].first;
				temp[j].second = arr[j - 1].second;
			}
			temp[i].first = score.first;
			temp[i].second = score.second;
			arr = temp;
			return;
		}
	}
}

int HighscoreManager::highscores::getLowest()
{
	return arr[4].first;
}

void HighscoreManager::setTexts()
{
	font.loadFromFile(std::filesystem::current_path().append("resources/images/slkscr.ttf").string());

	for (unsigned char i = 0; i < nameTexts.size(); i++)
	{
		nameTexts[i].setFont(font);
		nameTexts[i].setCharacterSize(50);
		nameTexts[i].setPosition(100, i * 100 + 250);
        scoreTexts[i].setFont(font);
        scoreTexts[i].setCharacterSize(50);
        scoreTexts[i].setPosition(600, i * 100 + 250);
	}
}

void HighscoreManager::setTextString()
{
	for (unsigned char i = 0; i < highScores.arr.size(); i++)
	{
        if (highScores.arr[i].first != 0)
        {
            std::ostringstream num;
            num << std::setfill('0') << std::setw(6) << highScores.arr[i].first;
            std::ostringstream name;
            name << std::left << std::setw(15) << highScores.arr[i].second;

            nameTexts[i].setString(std::to_string(i +1 ) + ". " + name.str());
            scoreTexts[i].setString(num.str());
        }
        else
        {
            scoreTexts[i].setString("000000");
			nameTexts[i].setString(std::to_string(i + 1) + ". empty");
        }
	}
}

void HighscoreManager::loadFromFile()
{
    std::ifstream file(std::filesystem::current_path().append("resources/highscore.xd").string());
    if (file.is_open())
    {
        std::string line;
        int i = 0;
        while (std::getline(file, line))
        {
            std::stringstream ss;
            ss << line;
            ss >> highScores.arr[i].first;
            ss >> highScores.arr[i].second;
            i++;
        }
    }
    file.close();
}

HighscoreManager::HighscoreManager()
{
    backTexture.loadFromFile(std::filesystem::current_path().append("resources/images/Highscores.png").string());
    nameTexture.loadFromFile(std::filesystem::current_path().append("resources/images/EnterName.png").string());
    backSprite.setTexture(backTexture);
    nameSprite.setTexture(nameTexture);

    loadFromFile();
	setTexts();
	setTextString();
}

HighscoreManager::~HighscoreManager()
{
	std::filesystem::path path = std::filesystem::current_path().append("resources/highscore.xd");

	std::ofstream file;
	file.open(path.string());
	if (file.is_open())
	{
		for (auto& el : highScores.arr)
		{
			file << el.first << " " << el.second << std::endl;
		}
	}
	file.close();
}

std::string HighscoreManager::getName(sf::RenderWindow* window, int score)
{
    TextBox textBox({ 100, 290 }, 83, window);
    sf::Text scoreText;
    std::ostringstream os;
    os << std::setfill('0') << std::setw(6) << score;
    scoreText.setString("your score: " + os.str());
    scoreText.setCharacterSize(70);
    scoreText.setPosition(33,400);
    scoreText.setFont(font);
    while (window->isOpen())
    {
        window->clear();
        textBox.update(window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && textBox.validName())
        {
            break;
        }
        window->draw(nameSprite);
        window->draw(scoreText);
        window->draw(textBox.getText());
        window->display();
    }
    if (textBox.validName())
        return *textBox.getName();
    else
        return "unnamed";
}

void HighscoreManager::update(int score, sf::RenderWindow* window)
{
	if (highScores.getLowest() < score)
	{
		highScores.saveSocore(std::make_pair(score, getName(window, score)));
	}
	setTextString();
}

void HighscoreManager::display(sf::RenderWindow* window)
{
    window->draw(backSprite);
    for (unsigned char i = 0; i < nameTexts.size(); i++)
    {
        window->draw(nameTexts[i]);
        window->draw(scoreTexts[i]);
    }
}
