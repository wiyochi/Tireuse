#include "Bouton.h"

Bouton::Bouton() :
	x(0), y(0), width(20), height(20), buttonColor(white), rect({ width, height })
{
}

Bouton::Bouton(float X, float Y, float w, float h, color c) :
	x(X), y(Y), width(w), height(h), buttonColor(c), rect({width, height})
{
	rect.setPosition({ x, y });
	//
	rect.setOutlineThickness(((1.f / 10.f * width) + (1.f / 10.f * height)) / 2.f);

	switch (buttonColor)
	{
	case red:
		rect.setFillColor(sf::Color::Red);
		rect.setOutlineColor(sf::Color(200, 0, 0));
		break;
	case blue:
		rect.setFillColor(sf::Color(0, 120, 200));
		rect.setOutlineColor(sf::Color(0, 80, 180));
		break;
	case green:
		rect.setFillColor(sf::Color::Green);
		rect.setOutlineColor(sf::Color(0, 200, 0));
		break;
	case white:
		rect.setFillColor(sf::Color::White);
		rect.setOutlineColor(sf::Color(200, 200, 200));
		break;
	default:
		rect.setFillColor(sf::Color::White);
		rect.setOutlineColor(sf::Color(200, 200, 200));
		break;
	}
}

Bouton::~Bouton()
{
}

void Bouton::draw(sf::RenderWindow & win)
{
	win.draw(rect);
}

void Bouton::click()
{
}
