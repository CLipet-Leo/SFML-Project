#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class CanonBall : public GameObject
{
public:
	CanonBall(float x, float y, sf::Color color, float radius, sf::Vector2f oOriginDirection);
	~CanonBall();
	//void Draw(sf::RenderWindow& window);
};
