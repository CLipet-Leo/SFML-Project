#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

namespace Math
{

	float fAngleRadiant(const sf::Vector2f& oVector1, const sf::Vector2f& oVector2);

	float fAngleDegrees(float fAngleRadian);

};

