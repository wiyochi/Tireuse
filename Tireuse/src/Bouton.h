#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Bouton
{
public:
	typedef enum
	{
		red,
		blue,
		green,
		white
	} color;

	Bouton();
	Bouton(float X, float Y, float w, float h, color c);
	~Bouton();
	void draw(sf::RenderWindow & win);
	void click();
private:
	color buttonColor;
	float x;
	float y;
	float width;
	float height;
	bool mouseOn;
	bool clicked;
	sf::RectangleShape rect;
};

