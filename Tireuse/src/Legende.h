#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

class Legende
{
public:
	const float Pi = 3.141592654f;

	typedef enum
	{
		Left,
		Right
	} Direction;
	Legende();
	Legende(sf::Vector2f point, sf::Vector2f legend, Direction dir, const wchar_t * text);
	~Legende();
	void draw(sf::RenderWindow & win);
	void setPoint(sf::Vector2f newPoint);
	void setLegend(sf::Vector2f newLegend);
	void setPos(sf::Vector2f newPoint, sf::Vector2f newLegend);
	void setDir(Direction newDir);
	void setText(std::string text);
	void change();

private:
	sf::Vector2f m_point;
	sf::Vector2f m_legend;
	Direction m_dir;
	sf::RectangleShape m_line;
	sf::RectangleShape m_under;
	sf::Text m_drawText;
	sf::Font font;
};

