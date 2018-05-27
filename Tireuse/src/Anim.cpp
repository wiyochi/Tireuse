#include "Anim.h"

Anim::Anim()
{
}

Anim::Anim(sf::Sprite * sprite, std::vector<sf::Vector2f> pos, float constSpeed) :
	m_positions(pos),
	m_indexObjectivePos(0),
	m_constSpeed(constSpeed),
	m_onOrigin(true),
	m_currentPos(sf::Vector2f(0, 0)),
	firstAnim(true)
{
	m_sprite = sprite;
}

Anim::~Anim()
{
}

void Anim::setPos(std::vector<sf::Vector2f> pos)
{
	m_positions = pos;
}

bool Anim::isAnimating()
{
	return m_animating;
}

void Anim::start()
{
	if (firstAnim)
	{
		firstPosX = m_sprite->getPosition().x;
		firstPosY = m_sprite->getPosition().y;
		firstAnim = false;
	}
	m_sprite->setPosition({ firstPosX, firstPosY });
	m_animating = true;
}

void Anim::stop()
{
	m_animating = false;
}

void Anim::setDir()
{
	dir_x = m_positions[m_indexObjectivePos].x;
	dir_y = m_positions[m_indexObjectivePos].y;
	m_distance = sqrtf(powf(m_positions[m_indexObjectivePos].y, 2) + powf(m_positions[m_indexObjectivePos].x, 2));
	m_speed = m_constSpeed / m_distance;
}

void Anim::next(float dt)
{
	float moveX;
	float moveY;

	if (m_animating)
	{
		if (m_onOrigin)
			this->setDir();

		moveX = roundf(this->adjust(dir_x * m_speed * dt));
		moveY = roundf(this->adjust(dir_y * m_speed * dt));

		//moveX = roundf(dir_x * m_speed * dt);
		//moveY = roundf(dir_y * m_speed * dt);

		m_sprite->move({ moveX, moveY });

		m_currentPos = m_currentPos + sf::Vector2f(moveX, moveY);
		m_onOrigin = false;

		if (m_currentPos == m_positions[m_indexObjectivePos])
		{
			if (m_positions.size() <= m_indexObjectivePos + 1)
			{
				m_animating = false;
				m_indexObjectivePos = 0;
				m_onOrigin = true;
				m_currentPos = sf::Vector2f(0, 0);
			}
			else
			{
				m_indexObjectivePos++;
				m_onOrigin = true;
				m_currentPos = sf::Vector2f(0, 0);
			}
		}
	}
}

float Anim::adjust(float value) const
{
	if (value < 1 && value > 0)
		return 1;
	else if (value < 0 && value > -1)
		return -1;
	else
		return value;
}
