#include <SFML/Graphics.hpp>

#include "../menu/MenuClass.h"

void main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Menu menu;
    menu.update();

    /*sf::Text a;
    a.setString("is");
    sf::Font c;
    c.loadFromFile("resources/images/slkscr.ttf");
    a.setPosition({ 100,200 });
    a.setFont(c);
    a.setCharacterSize(300);
    sf::RenderWindow window({ WINDOW_SIZE_X, WINDOW_SIZE_Y }, "Tetris", sf::Style::Titlebar | sf::Style::Close);
    while (true)
    {
        window.draw(a);
        window.display();
    }*/
}