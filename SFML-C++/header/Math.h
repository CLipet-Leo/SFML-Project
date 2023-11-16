#pragma once

#include <SFML/System/Vector2.hpp>

namespace Math
{
	sf::Vector2f DirectionBetweenPoints(const sf::Vector2f& oVector1, const sf::Vector2f& oVector2);

	float VectorToAngle(const sf::Vector2f& oVector1, const sf::Vector2f& oVector2);

	float VectorToNorm(const sf::Vector2f& oVector);

	sf::Vector2f NormalizedVector(const sf::Vector2f& oVector);
};
