#include <SFML/Graphics.hpp>

#include "GameApp.h"

void main()
{
    GameApp app(0);
    std::cout << "score: " << app.run() << std::endl;
}