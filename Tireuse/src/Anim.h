#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

class Anim
{
public:
	Anim();
	Anim(sf::Sprite * sprite, std::vector <sf::Vector2f> pos, float constSpeed);
	~Anim();
	void setPos(std::vector <sf::Vector2f> pos);
	bool isAnimating();
	void start();
	void stop();
	void setDir();
	void next(float dt);
	float adjust(float value) const;
private:
	sf::Sprite* m_sprite;
	std::vector <sf::Vector2f> m_positions;
	bool m_animating;
	unsigned int m_indexObjectivePos;
	bool m_onOrigin;
	sf::Vector2f m_currentPos;
	float m_speed;
	float m_constSpeed;
	float m_distance;
	float dir_x;
	float dir_y;
	float firstPosX;
	float firstPosY;
	bool firstAnim;
};
