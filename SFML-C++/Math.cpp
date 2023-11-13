#include "header/Math.h"

namespace Math
{
	float PI = static_cast<float>(180 / (atan(1) * 4));

	float Math::fAngleRadiant(const sf::Vector2f& oVector1, const sf::Vector2f& oVector2)
	{
		float fAngleRadian = -atan2(oVector1.x - oVector2.x, oVector1.y - oVector2.y);
		return fAngleRadian;
	}

	float Math::fAngleDegrees(float fAngleRadian)
	{
		float fAngleDegree = fAngleRadian * PI;
		return fAngleDegree + 180;
	}

}