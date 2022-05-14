#include <SFML/Graphics.hpp>
#include "../menu/MenuClass.h"
#include <regex>

constexpr auto BACKSPACE = 8;
constexpr auto ENTER = 13;
constexpr auto ESC = 27;

class TextBox
{
    sf::Text text;
    sf::Font font;
    std::string str;
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
        if (timer > 0.5f && timer < 1.f)
            showSlash = true;
        else if (timer > 1.f)
        {
            showSlash = false;
            timer = 0.f;
        }
    }

    void updateText(sf::Event event)
    {
        std::string temp = str;
        if (event.text.unicode == BACKSPACE && temp.size() > 0)
            temp.pop_back();
        else if (event.text.unicode != BACKSPACE && event.text.unicode != ENTER && event.text.unicode != ESC && temp.size() < 10)
            temp.push_back(event.text.unicode);

        str = temp;
        text.setString(str);
        timer = 0.5f;
        if (!validateText(temp))
            text.setFillColor(sf::Color::Red);
        else
            text.setFillColor(sf::Color::White);
    }

    bool validateText(std::string& temp)
    {
        std::regex nameReg("[0-9A-Za-z]{3,10}");
        return std::regex_match(temp, nameReg);
    }
    bool goodName()
    {
        std::regex nameReg("[0-9A-Za-z]{3,10}");
        return std::regex_match(str, nameReg);
    }

    sf::Text getText()
    {
        if (showSlash)
            text.setString(str + "|");
        else
            text.setString(str);
        return text;
    }
    std::string* getString()
    {
        return &str;
    }
};

void main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Menu menu;
    menu.update();

    /*sf::RenderWindow window({ WINDOW_SIZE_X, WINDOW_SIZE_Y }, "Tetris", sf::Style::Titlebar | sf::Style::Close);
    TextBox textbox({ 100,100 }, 30, &window);

    std::string name = "";
    while (window.isOpen())
    {
        window.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        textbox.update(&window);

        window.draw(textbox.getText());
        window.display();
    }*/
}