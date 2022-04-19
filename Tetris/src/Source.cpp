#include <SFML/Graphics.hpp>

#include "GameApp.h"

void main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    GameApp app(0);
    std::cout << "score: " << app.run() << std::endl;
}