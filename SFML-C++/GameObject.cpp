#include "header/GameObject.h"

using namespace std;

GameObject::GameObject(float x, float y, const sf::Color& color, float r)
	:x(x), y(y), color(color), radius(r)
{
	oCircle = new sf::CircleShape;
	oCircle->setRadius(radius);
	oCircle->setPosition(x, y);
	oCircle->setFillColor(color);

	oShape = oCircle;
}

GameObject::GameObject(float x, float y, const sf::Color& color, float w, float h)
	:x(x), y(y), color(color), width(w), height(h)
{
	oRectangle = new sf::RectangleShape;
	oRectangle->setSize(sf::Vector2f(w, h));
	//oRectangle->setPosition(x, y);
	oRectangle->setOrigin(x, y);
	oRectangle->setFillColor(color);

	oShape = oRectangle;
}

GameObject::~GameObject()
{
	delete oShape;
}

void GameObject::SetPosition(float fX, float fY, float fRatioX, float fRatioY)
{
	sf::Vector2f oOriginPosition = oShape->getOrigin();
	sf::Vector2f oRatioPosition = { width * fRatioX, height * fRatioY };
	if (fX != 0 && fY != 0)
		oShape->setPosition(oRatioPosition.x + fX , oRatioPosition.y + fY);
	else
	{
		oShape->setPosition(oRatioPosition.x + oOriginPosition.x, oRatioPosition.y + oOriginPosition.y);
		oShape->setOrigin(oRatioPosition.x + oOriginPosition.x, oRatioPosition.y + oOriginPosition.y);
	}
}

void GameObject::SetRotation(float fAngle, float fRatioX, float fRatioY)
{

}

void GameObject::Draw(sf::RenderWindow& window)
{
	window.draw(*oShape);
}

void GameObject::SetDirection(float fX, float fY)
{
	sf::Vector2f speedVect = { fX , fY };
	oDirection = Math::NormalizedVector(speedVect);
	cout << "Direction : " << speedVect.x << "," << speedVect.y;
}

void GameObject::Move(float fDeltaTime)
{
	oVect = oShape->getOrigin();
	sf::Vector2f oVectInit = { oVect.x * oDirection.x * 100 * fDeltaTime, oVect.y * oDirection.x * 100 * fDeltaTime };
	cout << "Nouvelle pos : ", oVectInit.x, ",", oVectInit.y;
	SetPosition(oVectInit.x, oVectInit.y);
}

void GameObject::CheckCollisions(const GameObject& goOther)
{

}

void GameObject::Rotate(sf::Vector2i& oOrientationPosition)
{
	sf::Vector2f oOriginPositionInWindow = GetOriginRelativeToWindow();
	sf::Vector2f fOrientationPosition = { static_cast<float>(oOrientationPosition.x + (width/2)), static_cast<float>(oOrientationPosition.y) };

	float fAngleDegree = Math::VectorToAngle(fOrientationPosition, oOriginPositionInWindow);

	//std::cout << fAngleDegree << std::endl;

	oShape->setRotation(fAngleDegree);
}

sf::Vector2f GameObject::GetOriginRelativeToWindow()
{
	oShape->setOrigin(width / 2, height);
	sf::Vector2f oWindowPosition = oShape->getPosition();
	sf::Vector2f oOriginPosition = oShape->getOrigin();

	return oWindowPosition + oOriginPosition;
}