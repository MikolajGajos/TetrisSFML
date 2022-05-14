#include <SFML/Graphics.hpp>
#include "../menu/MenuClass.h"
#include <regex>

void main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Menu menu;
    menu.update();

    //sf::Text a;
    //a.setString("select level");
    //sf::Font c;
    //c.loadFromFile("resources/images/slkscr.ttf");
    //a.setPosition({ 100,200 });
    //a.setFont(c);
    //a.setCharacterSize(50);

    /*TextBox textbox({ 100,100 }, 50);

    sf::RenderWindow window({ WINDOW_SIZE_X, WINDOW_SIZE_Y }, "Tetris", sf::Style::Titlebar | sf::Style::Close);

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