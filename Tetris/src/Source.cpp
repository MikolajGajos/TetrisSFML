#include <SFML/Graphics.hpp>

#include "GameApp.h"

int main()
{	
	GameApp app(0);

	std::cout << "score: " << app.run() << std::endl;

	/*sf::RenderWindow window(sf::VideoMode(800, 600), "xd");
	sf::Font font;
	font.loadFromFile("src/rsrc/slkscr.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(150);
	text.setString("GAME\nOVER");
	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		window.draw(text);
		window.display();
	}*/
}