#include <SFML/Graphics.hpp>
#include "Bouton.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "SFML works!");
	Bouton B(100, 100, 200, 50, Bouton::color::blue);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		B.draw(window);
		window.display();
	}

	return 0;
}