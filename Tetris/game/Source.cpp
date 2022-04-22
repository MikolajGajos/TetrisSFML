#include <SFML/Graphics.hpp>

#include "headers/GameApp.h"
#include "headers/Button.h"
void main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    sf::RenderWindow window({ WINDOW_SIZE_X, WINDOW_SIZE_Y }, "Tetris", sf::Style::Close | sf::Style::Default);

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            GameApp app(&window, 0);
            std::cout << "score: " << app.run() << std::endl;
            window.close();
        }
        window.display();
    }
}