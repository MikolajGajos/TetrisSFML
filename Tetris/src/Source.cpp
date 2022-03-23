#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "GameApp.h"

int main()
{
	GameApp app(19);

	std::cout << "score: " << app.run() << std::endl;
}