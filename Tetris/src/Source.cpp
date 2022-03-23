#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "GameApp.h"

int main()
{
	GameApp app(5);

	std::cout << "score: " << app.run() << std::endl;
}