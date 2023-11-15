#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

namespace Math
{
	float VectorToAngle(const sf::Vector2f& oVector1, const sf::Vector2f& oVector2);

	float VectorToNorm(const sf::Vector2f& oVector);

	sf::Vector2f NormalizedVector(const sf::Vector2f& oVector);

};