#include "header/GameObject.h"

#include "header/Math.h"

#include <iostream>
#include "header/CanonBall.h"

using namespace std;

GameObject::GameObject(float x, float y, const sf::Color& color, float r)
	:x(x), y(y), color(color), radius(r)
{
	oCircle = new sf::CircleShape;
	oCircle->setRadius(radius);
	oCircle->setFillColor(color);

	oShape = oCircle;

	SetPosition(x, y);
}

GameObject::GameObject(float x, float y, const sf::Color& color, float w, float h)
	:x(x), y(y), color(color), width(w), height(h)
{
	oRectangle = new sf::RectangleShape;
	oRectangle->setSize(sf::Vector2f(w, h));
	oRectangle->setFillColor(color);

	oShape = oRectangle;

	SetPosition(x, y);
}

GameObject::~GameObject()
{
	delete oShape;
}

void GameObject::SetPosition(float fX, float fY, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);

	oShape->setPosition(fX, fY);
}

void GameObject::SetRotation(float fAngle, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);

	oShape->setRotation(fAngle);
}

void GameObject::SetOrigin(float fRatioX, float fRatioY) 
{
	float fOriginX = fRatioX * width;
	float fOriginY = fRatioY * height;

	oShape->setOrigin(fOriginX, fOriginY);
}

void GameObject::SetRotation(sf::Vector2i& oOrientationPosition, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);
	sf::Vector2f oOriginPositionInWindow = GetOriginRelativeToWindow();
	sf::Vector2f fOrientationPosition = { static_cast<float>(oOrientationPosition.x + (width / 2)), static_cast<float>(oOrientationPosition.y) };

	float fAngleDegree = Math::VectorToAngle(fOrientationPosition, oOriginPositionInWindow);

	sf::Vector2f oVectDirection = Math::DirectionBetweenPoints(oOriginPositionInWindow, fOrientationPosition);
	SetDirection(oVectDirection.x, oVectDirection.y * (-1));

	SetRotation(fAngleDegree, fRatioX, fRatioY);
}

void GameObject::Draw(sf::RenderWindow& window)
{
	if (typeid(*this) == typeid(CanonBall))
	{
		cout << "draw" << endl;
	}
	window.draw(*oShape);
}

void GameObject::SetDirection(float fX, float fY)
{
	sf::Vector2f speedVect = { fX , fY };
	oDirection = Math::NormalizedVector(speedVect);
}

void GameObject::Move(float fDeltaTime)
{
	if (typeid(*this) == typeid(CanonBall))
	{
		cout << "move" << endl;
	}
	oOriginVect = oShape->getPosition();
	oOriginVect.x += (oDirection.x * 100) * fDeltaTime;
	oOriginVect.y += (oDirection.y * 100) * fDeltaTime;
	SetPosition(oOriginVect.x, oOriginVect.y);
}

void GameObject::CheckCollisions(GameObject* goOther)
{

}

const sf::Vector2f GameObject::GetOriginRelativeToWindow()
{
	sf::Vector2f oWindowPosition = oShape->getPosition();
	sf::Vector2f oOriginPosition = oShape->getOrigin();

	return oWindowPosition + oOriginPosition;
}

const sf::Vector2f GameObject::GetPosition()
{
	return oShape->getPosition();
}


const sf::Vector2f GameObject::GetDirection()
{
	return oDirection;
}