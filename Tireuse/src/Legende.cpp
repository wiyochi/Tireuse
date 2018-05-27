#include "Legende.h"

Legende::Legende()
{
	Legende({ 10 , 10 }, { 0 , 0 }, Left, L"legend");
}

Legende::Legende(sf::Vector2f point, sf::Vector2f legend, Direction dir, const wchar_t * text) :
	m_point(point),
	m_legend(legend),
	m_dir(dir),
	m_line({ sqrtf(powf(fabsf(m_point.x - m_legend.x), 2) + powf(fabsf(m_point.y - m_legend.y), 2)), 3.f })
{
	m_line.setFillColor(sf::Color::Black);
	m_line.setPosition(m_legend);

	if (m_point.x >= m_legend.x && m_point.y >= m_legend.y)
	{
		m_line.rotate((atanf(fabsf(m_point.y - m_legend.y) / fabsf(m_point.x - m_legend.x))) / Pi * 180);
	}
	else if (m_point.x < m_legend.x && m_point.y >= m_legend.y)
	{
		m_line.rotate(180 - ((atanf(fabsf(m_point.y - m_legend.y) / fabsf(m_point.x - m_legend.x))) / Pi * 180));
	}
	else if (m_point.x < m_legend.x && m_point.y < m_legend.y)
	{
		m_line.rotate(180 + ((atanf(fabsf(m_point.y - m_legend.y) / fabsf(m_point.x - m_legend.x))) / Pi * 180));
	}
	else
	{
		m_line.rotate(-((atanf(fabsf(m_point.y - m_legend.y) / fabsf(m_point.x - m_legend.x))) / Pi * 180));
	}

	font.loadFromFile("ressources/Aver.ttf");
	m_drawText.setFont(font);
	m_drawText.setString(text);
	m_drawText.setCharacterSize(20);
	m_drawText.setFillColor(sf::Color::Black);

	m_under.setFillColor(sf::Color::Black);
	m_under.setSize({ m_drawText.getGlobalBounds().width + 5 , 3.f });
	if (m_dir == Direction::Left)
	{
		m_drawText.setPosition({ m_legend.x - m_drawText.getGlobalBounds().width - 5 , m_legend.y - m_drawText.getGlobalBounds().height - 5 });
		m_under.setPosition({ m_legend.x - m_drawText.getGlobalBounds().width - 5 , m_legend.y });
	}
	else
	{
		m_drawText.setPosition({ m_legend.x + 5 , m_legend.y - m_drawText.getGlobalBounds().height - 5 });
		m_under.setPosition({ m_legend.x , m_legend.y });
	}
}

Legende::~Legende()
{
}

void Legende::draw(sf::RenderWindow & win)
{
	win.draw(m_line);
	win.draw(m_under);
	win.draw(m_drawText);
}

void Legende::setPoint(sf::Vector2f newPoint)
{
	m_point = newPoint;
	change();
}

void Legende::setLegend(sf::Vector2f newLegend)
{
	m_legend = newLegend;
	change();
}

void Legende::setPos(sf::Vector2f newPoint, sf::Vector2f newLegend)
{
	m_legend = newLegend;
	m_point = newPoint;
	change();
}

void Legende::setDir(Direction newDir)
{
	m_dir = newDir;
	change();
}

void Legende::setText(std::string text)
{
	m_drawText.setString(text);
	change();
}

void Legende::change()
{
	m_line.setPosition(m_legend);
	m_line.setSize({ sqrtf(powf(fabsf(m_point.x - m_legend.x), 2) + powf(fabsf(m_point.y - m_legend.y), 2)), 3.f });

	if (m_point.x >= m_legend.x && m_point.y >= m_legend.y)
	{
		m_line.setRotation((atanf(fabsf(m_point.y - m_legend.y) / fabsf(m_point.x - m_legend.x))) / Pi * 180);
	}
	else if (m_point.x < m_legend.x && m_point.y >= m_legend.y)
	{
		m_line.setRotation(180 - ((atanf(fabsf(m_point.y - m_legend.y) / fabsf(m_point.x - m_legend.x))) / Pi * 180));
	}
	else if (m_point.x < m_legend.x && m_point.y < m_legend.y)
	{
		m_line.setRotation(180 + ((atanf(fabsf(m_point.y - m_legend.y) / fabsf(m_point.x - m_legend.x))) / Pi * 180));
	}
	else
	{
		m_line.setRotation(-((atanf(fabsf(m_point.y - m_legend.y) / fabsf(m_point.x - m_legend.x))) / Pi * 180));
	}
	m_drawText.setPosition({ m_legend.x - m_drawText.getGlobalBounds().width - 5 , m_legend.y - m_drawText.getGlobalBounds().height - 5 });
	m_under.setSize({ m_drawText.getGlobalBounds().width + 5 , 3.f });
	if (m_dir == Direction::Left)
	{
		m_drawText.setPosition({ m_legend.x - m_drawText.getGlobalBounds().width - 5 , m_legend.y - m_drawText.getGlobalBounds().height - 5 });
		m_under.setPosition({ m_legend.x - m_drawText.getGlobalBounds().width - 5 , m_legend.y });
	}
	else
	{
		m_drawText.setPosition({ m_legend.x + 5 , m_legend.y - m_drawText.getGlobalBounds().height - 5 });
		m_under.setPosition({ m_legend.x , m_legend.y - 1 });
	}
}
