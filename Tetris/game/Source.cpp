#include <SFML/Graphics.hpp>

#include "../menu/MenuClass.h"

void main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    Menu menu;
    menu.update();


    /*sf::RenderWindow window({ WINDOW_SIZE_X, WINDOW_SIZE_Y }, "Tetris", sf::Style::Close | sf::Style::Default);

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            GameApp app(&window);
            std::cout << "score: " << app.run() << std::endl;
            window.close();
        }
        window.display();
    }*/

    /*Button resume(0, 100, 50, 100, 50);
    Button but(1, 100, 150, 100, 50);
    Button exit(2, 100, 250, 100, 50);
    Button nwm(3, 100, 350, 200, 50);
    ButtonManager bbbb{ exit, resume, but, nwm };

    while (window.isOpen())
    {
        sf::Event event;
        (window).pollEvent(event);
        if (event.type == sf::Event::Closed)
            (window).close();

        window.clear(sf::Color::Black);

        bbbb.update(window);

        window.draw(bbbb);
        window.display();
    }*/
}