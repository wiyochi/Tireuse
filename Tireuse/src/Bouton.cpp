#include "Bouton.h"

Bouton::Bouton()
{
	Bouton(0, 0, 20, 20, sf::Color::White, "Bouton");
}

Bouton::Bouton(float X, float Y, float w, float h, sf::Color c, std::string t) :
	x(X), y(Y), width(w), widthMin(width), widthMax(width + width / 2.f), height(h), rect({width, height}), mouseOn(false), change(false), m_clicked(false)
{
	str = t;

	rect.setPosition({ x, y });
	rect.setFillColor(c);

	font.loadFromFile("ressources/Aver.ttf");
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(30);

	float textCenterY = (rect.getSize().y) - (text.getGlobalBounds().height);
	textCenterY = textCenterY / 2.f;
	float textCenterX = (rect.getSize().x) - (text.getGlobalBounds().width);
	textCenterX = textCenterX / 2.f;

	text.setPosition(x + textCenterX - (((1.f / 16.f * width) + (1.f / 16.f * height)) / 2.f), y + textCenterY - (((1.f / 16.f * width) + (1.f / 16.f * height)) / 2.f));
}

Bouton::~Bouton()
{
}

void Bouton::update(float dt, sf::RenderWindow & win)
{
	mouse(win);
	click(win);

	if (mouseOn && width < widthMax)
	{
		width += dt * 80 * ((widthMax - width)/10 + 1);
	}
	if (!mouseOn && width > widthMin)
	{
		width -= dt * 80 * ((width - widthMin) / 10 + 1);
	}
	rect.setSize({ width, height });
}

void Bouton::draw(sf::RenderWindow & win)
{
	win.draw(rect);
	win.draw(text);
}

void Bouton::mouse(sf::RenderWindow & win)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(win);

	if (mousePos.x > x && mousePos.x < x + width && mousePos.y > y && mousePos.y < y + height)
	{
		mouseOn = true;
		if (!change)
		{
			rect.setFillColor(rect.getFillColor() + sf::Color(30, 30, 30, 0));
			text.setFillColor(text.getFillColor() - sf::Color(0, 0, 0, 75));
			change = true;
		}
	}
	else
	{
		mouseOn = false;
		if (change)
		{
			rect.setFillColor(rect.getFillColor() - sf::Color(30, 30, 30, 0));
			text.setFillColor(text.getFillColor() + sf::Color(0, 0, 0, 75));
			change = false;
		}
	}
}

void Bouton::click(sf::RenderWindow & win)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(win);

	if (mousePos.x > x && mousePos.x < x + width && mousePos.y > y && mousePos.y < y + height
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_clicked = true;
	}
	else if (!(mousePos.x > x && mousePos.x < x + width && mousePos.y > y && mousePos.y < y + height)
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_clicked = false;
	}
}

bool Bouton::clicked()
{
	return m_clicked;
}
