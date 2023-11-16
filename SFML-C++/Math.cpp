#include "header/Math.h"

#include <cmath>

namespace Math
{
	float PI = 3.14159265358979323846;

	sf::Vector2f Math::DirectionBetweenPoints(const sf::Vector2f& oVector1, const sf::Vector2f& oVector2)
	{
		sf::Vector2f oVectDirection = { (oVector2.x - oVector1.x), (oVector2.y - oVector1.y) };
		return oVectDirection;
	}

	float Math::VectorToAngle(const sf::Vector2f& oVector1, const sf::Vector2f& oVector2)
	{
		float fAngleRadian = -atan2(oVector1.x - oVector2.x, oVector1.y - oVector2.y);
		float fAngleDegree = fAngleRadian * 180 / PI;

		return fAngleDegree + 180;
	}

	float Math::VectorToNorm(const sf::Vector2f& oVector)
	{
		return sqrt((oVector.x * oVector.x) + (oVector.y * oVector.y));
	}

	sf::Vector2f Math::NormalizedVector(const sf::Vector2f& oVector)
	{
		float oNorm = VectorToNorm(oVector);
		sf::Vector2f oNormalizedVector = { oVector.x / oNorm, oVector.y / oNorm};
		return oNormalizedVector;
	}
}