#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

class Bouton
{
public:
	Bouton();
	Bouton(float X, float Y, float w, float h, sf::Color c, std::string t);
	~Bouton();
	void update(float dt, sf::RenderWindow & win);
	void draw(sf::RenderWindow & win);
	void mouse(sf::RenderWindow & win);
	void click(sf::RenderWindow & win);
	bool clicked();
private:
	float x;
	float y;
	float width;
	float widthMin;
	float widthMax;
	float height;
	bool change;
	std::string str;
	bool mouseOn;
	bool m_clicked;
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;
};

